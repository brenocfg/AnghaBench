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
typedef  TYPE_1__ macaddr_sortsupport_state ;
typedef  int /*<<< orphan*/  macaddr ;
struct TYPE_5__ {TYPE_1__* ssup_extra; } ;
typedef  TYPE_2__* SortSupport ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 scalar_t__ DatumBigEndianToNative (scalar_t__) ; 
 int /*<<< orphan*/ * DatumGetMacaddrP (scalar_t__) ; 
 int /*<<< orphan*/  DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 int SIZEOF_DATUM ; 
 int /*<<< orphan*/  addHyperLogLog (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_uint32 (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Datum
macaddr_abbrev_convert(Datum original, SortSupport ssup)
{
	macaddr_sortsupport_state *uss = ssup->ssup_extra;
	macaddr    *authoritative = DatumGetMacaddrP(original);
	Datum		res;

	/*
	 * On a 64-bit machine, zero out the 8-byte datum and copy the 6 bytes of
	 * the MAC address in. There will be two bytes of zero padding on the end
	 * of the least significant bits.
	 */
#if SIZEOF_DATUM == 8
	memset(&res, 0, SIZEOF_DATUM);
	memcpy(&res, authoritative, sizeof(macaddr));
#else							/* SIZEOF_DATUM != 8 */
	memcpy(&res, authoritative, SIZEOF_DATUM);
#endif
	uss->input_count += 1;

	/*
	 * Cardinality estimation. The estimate uses uint32, so on a 64-bit
	 * architecture, XOR the two 32-bit halves together to produce slightly
	 * more entropy. The two zeroed bytes won't have any practical impact on
	 * this operation.
	 */
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

	/*
	 * Byteswap on little-endian machines.
	 *
	 * This is needed so that macaddr_cmp_abbrev() (an unsigned integer 3-way
	 * comparator) works correctly on all platforms. Without this, the
	 * comparator would have to call memcmp() with a pair of pointers to the
	 * first byte of each abbreviated key, which is slower.
	 */
	res = DatumBigEndianToNative(res);

	return res;
}