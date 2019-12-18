#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int input_count; int /*<<< orphan*/  abbr_card; scalar_t__ estimating; } ;
typedef  TYPE_1__ uuid_sortsupport_state ;
typedef  int uint64 ;
typedef  int uint32 ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ pg_uuid_t ;
struct TYPE_8__ {TYPE_1__* ssup_extra; } ;
typedef  TYPE_3__* SortSupport ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 scalar_t__ DatumBigEndianToNative (scalar_t__) ; 
 int /*<<< orphan*/  DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 TYPE_2__* DatumGetUUIDP (scalar_t__) ; 
 int /*<<< orphan*/  addHyperLogLog (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_uint32 (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Datum
uuid_abbrev_convert(Datum original, SortSupport ssup)
{
	uuid_sortsupport_state *uss = ssup->ssup_extra;
	pg_uuid_t  *authoritative = DatumGetUUIDP(original);
	Datum		res;

	memcpy(&res, authoritative->data, sizeof(Datum));
	uss->input_count += 1;

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
	 * This is needed so that uuid_cmp_abbrev() (an unsigned integer 3-way
	 * comparator) works correctly on all platforms.  If we didn't do this,
	 * the comparator would have to call memcmp() with a pair of pointers to
	 * the first byte of each abbreviated key, which is slower.
	 */
	res = DatumBigEndianToNative(res);

	return res;
}