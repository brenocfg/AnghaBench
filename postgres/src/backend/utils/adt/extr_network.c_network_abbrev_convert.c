#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
typedef  int uint32 ;
struct TYPE_4__ {int input_count; int /*<<< orphan*/  abbr_card; scalar_t__ estimating; } ;
typedef  TYPE_1__ network_sortsupport_state ;
typedef  int /*<<< orphan*/  inet ;
struct TYPE_5__ {TYPE_1__* ssup_extra; } ;
typedef  TYPE_2__* SortSupport ;
typedef  int Datum ;

/* Variables and functions */
 int ABBREV_BITS_INET4_NETMASK_SIZE ; 
 int ABBREV_BITS_INET4_SUBNET ; 
 int /*<<< orphan*/  Assert (int) ; 
 int BITS_PER_BYTE ; 
 int DatumBigEndianToNative (int) ; 
 int /*<<< orphan*/ * DatumGetInetPP (int) ; 
 int /*<<< orphan*/  DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ PGSQL_AF_INET ; 
 scalar_t__ PGSQL_AF_INET6 ; 
 int SIZEOF_DATUM ; 
 int /*<<< orphan*/  addHyperLogLog (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_uint32 (int) ; 
 int /*<<< orphan*/  ip_addr (int /*<<< orphan*/ *) ; 
 int ip_bits (int /*<<< orphan*/ *) ; 
 scalar_t__ ip_family (int /*<<< orphan*/ *) ; 
 int ip_maxbits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int pg_bswap32 (int) ; 

__attribute__((used)) static Datum
network_abbrev_convert(Datum original, SortSupport ssup)
{
	network_sortsupport_state *uss = ssup->ssup_extra;
	inet	   *authoritative = DatumGetInetPP(original);
	Datum		res,
				ipaddr_datum,
				subnet_bitmask,
				network;
	int			subnet_size;

	Assert(ip_family(authoritative) == PGSQL_AF_INET ||
		   ip_family(authoritative) == PGSQL_AF_INET6);

	/*
	 * Get an unsigned integer representation of the IP address by taking its
	 * first 4 or 8 bytes. Always take all 4 bytes of an IPv4 address. Take
	 * the first 8 bytes of an IPv6 address with an 8 byte datum and 4 bytes
	 * otherwise.
	 *
	 * We're consuming an array of unsigned char, so byteswap on little endian
	 * systems (an inet's ipaddr field stores the most significant byte
	 * first).
	 */
	if (ip_family(authoritative) == PGSQL_AF_INET)
	{
		uint32		ipaddr_datum32;

		memcpy(&ipaddr_datum32, ip_addr(authoritative), sizeof(uint32));

		/* Must byteswap on little-endian machines */
#ifndef WORDS_BIGENDIAN
		ipaddr_datum = pg_bswap32(ipaddr_datum32);
#else
		ipaddr_datum = ipaddr_datum32;
#endif

		/* Initialize result without setting ipfamily bit */
		res = (Datum) 0;
	}
	else
	{
		memcpy(&ipaddr_datum, ip_addr(authoritative), sizeof(Datum));

		/* Must byteswap on little-endian machines */
		ipaddr_datum = DatumBigEndianToNative(ipaddr_datum);

		/* Initialize result with ipfamily (most significant) bit set */
		res = ((Datum) 1) << (SIZEOF_DATUM * BITS_PER_BYTE - 1);
	}

	/*
	 * ipaddr_datum must be "split": high order bits go in "network" component
	 * of abbreviated key (often with zeroed bits at the end due to masking),
	 * while low order bits go in "subnet" component when there is space for
	 * one. This is often accomplished by generating a temp datum subnet
	 * bitmask, which we may reuse later when generating the subnet bits
	 * themselves.  (Note that subnet bits are only used with IPv4 datums on
	 * platforms where datum is 8 bytes.)
	 *
	 * The number of bits in subnet is used to generate a datum subnet
	 * bitmask. For example, with a /24 IPv4 datum there are 8 subnet bits
	 * (since 32 - 24 is 8), so the final subnet bitmask is B'1111 1111'. We
	 * need explicit handling for cases where the ipaddr bits cannot all fit
	 * in a datum, though (otherwise we'd incorrectly mask the network
	 * component with IPv6 values).
	 */
	subnet_size = ip_maxbits(authoritative) - ip_bits(authoritative);
	Assert(subnet_size >= 0);
	/* subnet size must work with prefix ipaddr cases */
	subnet_size %= SIZEOF_DATUM * BITS_PER_BYTE;
	if (ip_bits(authoritative) == 0)
	{
		/* Fit as many ipaddr bits as possible into subnet */
		subnet_bitmask = ((Datum) 0) - 1;
		network = 0;
	}
	else if (ip_bits(authoritative) < SIZEOF_DATUM * BITS_PER_BYTE)
	{
		/* Split ipaddr bits between network and subnet */
		subnet_bitmask = (((Datum) 1) << subnet_size) - 1;
		network = ipaddr_datum & ~subnet_bitmask;
	}
	else
	{
		/* Fit as many ipaddr bits as possible into network */
		subnet_bitmask = 0;
		network = ipaddr_datum;
	}

#if SIZEOF_DATUM == 8
	if (ip_family(authoritative) == PGSQL_AF_INET)
	{
		/*
		 * IPv4 with 8 byte datums: keep all 32 netmasked bits, netmask size,
		 * and most significant 25 subnet bits
		 */
		Datum		netmask_size = (Datum) ip_bits(authoritative);
		Datum		subnet;

		/*
		 * Shift left 31 bits: 6 bits netmask size + 25 subnet bits.
		 *
		 * We don't make any distinction between network bits that are zero
		 * due to masking and "true"/non-masked zero bits.  An abbreviated
		 * comparison that is resolved by comparing a non-masked and non-zero
		 * bit to a masked/zeroed bit is effectively resolved based on
		 * ip_bits(), even though the comparison won't reach the netmask_size
		 * bits.
		 */
		network <<= (ABBREV_BITS_INET4_NETMASK_SIZE +
					 ABBREV_BITS_INET4_SUBNET);

		/* Shift size to make room for subnet bits at the end */
		netmask_size <<= ABBREV_BITS_INET4_SUBNET;

		/* Extract subnet bits without shifting them */
		subnet = ipaddr_datum & subnet_bitmask;

		/*
		 * If we have more than 25 subnet bits, we can't fit everything. Shift
		 * subnet down to avoid clobbering bits that are only supposed to be
		 * used for netmask_size.
		 *
		 * Discarding the least significant subnet bits like this is correct
		 * because abbreviated comparisons that are resolved at the subnet
		 * level must have had equal netmask_size/ip_bits() values in order to
		 * get that far.
		 */
		if (subnet_size > ABBREV_BITS_INET4_SUBNET)
			subnet >>= subnet_size - ABBREV_BITS_INET4_SUBNET;

		/*
		 * Assemble the final abbreviated key without clobbering the ipfamily
		 * bit that must remain a zero.
		 */
		res |= network | netmask_size | subnet;
	}
	else
#endif
	{
		/*
		 * 4 byte datums, or IPv6 with 8 byte datums: Use as many of the
		 * netmasked bits as will fit in final abbreviated key. Avoid
		 * clobbering the ipfamily bit that was set earlier.
		 */
		res |= network >> 1;
	}

	uss->input_count += 1;

	/* Hash abbreviated key */
	if (uss->estimating)
	{
		uint32		tmp;

#if SIZEOF_DATUM == 8
		tmp = (uint32) res ^ (uint32) ((uint64) res >> 32);
#else							/* SIZEOF_DATUM != 8 */
		tmp = (uint32) res;
#endif

		addHyperLogLog(&uss->abbr_card, DatumGetUInt32(hash_uint32(tmp)));
	}

	return res;
}