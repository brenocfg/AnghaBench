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
typedef  int /*<<< orphan*/  json_writer_t ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  jsonw_printf (int /*<<< orphan*/ *,char*,scalar_t__,...) ; 

__attribute__((used)) static void btf_int128_print(json_writer_t *jw, const void *data,
			     bool is_plain_text)
{
	/* data points to a __int128 number.
	 * Suppose
	 *     int128_num = *(__int128 *)data;
	 * The below formulas shows what upper_num and lower_num represents:
	 *     upper_num = int128_num >> 64;
	 *     lower_num = int128_num & 0xffffffffFFFFFFFFULL;
	 */
	__u64 upper_num, lower_num;

#ifdef __BIG_ENDIAN_BITFIELD
	upper_num = *(__u64 *)data;
	lower_num = *(__u64 *)(data + 8);
#else
	upper_num = *(__u64 *)(data + 8);
	lower_num = *(__u64 *)data;
#endif

	if (is_plain_text) {
		if (upper_num == 0)
			jsonw_printf(jw, "0x%llx", lower_num);
		else
			jsonw_printf(jw, "0x%llx%016llx", upper_num, lower_num);
	} else {
		if (upper_num == 0)
			jsonw_printf(jw, "\"0x%llx\"", lower_num);
		else
			jsonw_printf(jw, "\"0x%llx%016llx\"", upper_num, lower_num);
	}
}