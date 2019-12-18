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
typedef  scalar_t__ u64 ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__,...) ; 

__attribute__((used)) static void btf_int128_print(struct seq_file *m, void *data)
{
	/* data points to a __int128 number.
	 * Suppose
	 *     int128_num = *(__int128 *)data;
	 * The below formulas shows what upper_num and lower_num represents:
	 *     upper_num = int128_num >> 64;
	 *     lower_num = int128_num & 0xffffffffFFFFFFFFULL;
	 */
	u64 upper_num, lower_num;

#ifdef __BIG_ENDIAN_BITFIELD
	upper_num = *(u64 *)data;
	lower_num = *(u64 *)(data + 8);
#else
	upper_num = *(u64 *)(data + 8);
	lower_num = *(u64 *)data;
#endif
	if (upper_num == 0)
		seq_printf(m, "0x%llx", lower_num);
	else
		seq_printf(m, "0x%llx%016llx", upper_num, lower_num);
}