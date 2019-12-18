#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  HASH_KEY ;

/* Variables and functions */
 int BMPCACHE2_NUM_PSTCELLS ; 
 scalar_t__ MIN (scalar_t__,int) ; 
 scalar_t__ PDU_FLAG_FIRST ; 
 scalar_t__ PDU_FLAG_LAST ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  out_uint8a (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pstcache_enumerate (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdp_init_data (int) ; 
 int /*<<< orphan*/  rdp_send_data (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rdp_enum_bmpcache2(void)
{
	STREAM s;
	HASH_KEY keylist[BMPCACHE2_NUM_PSTCELLS];
	uint32 num_keys, offset, count, flags;

	offset = 0;
	num_keys = pstcache_enumerate(2, keylist);

	while (offset < num_keys)
	{
		count = MIN(num_keys - offset, 169);

		s = rdp_init_data(24 + count * sizeof(HASH_KEY));

		flags = 0;
		if (offset == 0)
			flags |= PDU_FLAG_FIRST;
		if (num_keys - offset <= 169)
			flags |= PDU_FLAG_LAST;

		/* header */
		out_uint32_le(s, 0);
		out_uint16_le(s, count);
		out_uint16_le(s, 0);
		out_uint16_le(s, 0);
		out_uint16_le(s, 0);
		out_uint16_le(s, 0);
		out_uint16_le(s, num_keys);
		out_uint32_le(s, 0);
		out_uint32_le(s, flags);

		/* list */
		out_uint8a(s, keylist[offset], count * sizeof(HASH_KEY));

		s_mark_end(s);
		rdp_send_data(s, 0x2b);

		offset += 169;
	}
}