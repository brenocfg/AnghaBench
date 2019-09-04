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
typedef  int uint8_t ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 
 int udf_name_from_CS0 (struct super_block*,int*,int,int const*,int,int /*<<< orphan*/ ) ; 

int udf_dstrCS0toChar(struct super_block *sb, uint8_t *utf_o, int o_len,
		      const uint8_t *ocu_i, int i_len)
{
	int s_len = 0;

	if (i_len > 0) {
		s_len = ocu_i[i_len - 1];
		if (s_len >= i_len) {
			pr_warn("incorrect dstring lengths (%d/%d),"
				" truncating\n", s_len, i_len);
			s_len = i_len - 1;
			/* 2-byte encoding? Need to round properly... */
			if (ocu_i[0] == 16)
				s_len -= (s_len - 1) & 2;
		}
	}

	return udf_name_from_CS0(sb, utf_o, o_len, ocu_i, s_len, 0);
}