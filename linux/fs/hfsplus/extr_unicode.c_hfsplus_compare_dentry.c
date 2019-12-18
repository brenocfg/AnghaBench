#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wchar_t ;
typedef  scalar_t__ u16 ;
struct super_block {int dummy; } ;
struct qstr {char* name; int len; } ;
struct dentry {struct super_block* d_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 TYPE_1__* HFSPLUS_SB (struct super_block*) ; 
 int /*<<< orphan*/  HFSPLUS_SB_CASEFOLD ; 
 int /*<<< orphan*/  HFSPLUS_SB_NODECOMPOSE ; 
 int asc2unichar (struct super_block*,char const*,int,scalar_t__*) ; 
 scalar_t__ case_fold (scalar_t__) ; 
 scalar_t__* decompose_unichar (scalar_t__,int*,scalar_t__*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hfsplus_compare_dentry(const struct dentry *dentry,
		unsigned int len, const char *str, const struct qstr *name)
{
	struct super_block *sb = dentry->d_sb;
	int casefold, decompose, size;
	int dsize1, dsize2, len1, len2;
	const u16 *dstr1, *dstr2;
	const char *astr1, *astr2;
	u16 c1, c2;
	wchar_t c;
	u16 dhangul_1[3], dhangul_2[3];

	casefold = test_bit(HFSPLUS_SB_CASEFOLD, &HFSPLUS_SB(sb)->flags);
	decompose = !test_bit(HFSPLUS_SB_NODECOMPOSE, &HFSPLUS_SB(sb)->flags);
	astr1 = str;
	len1 = len;
	astr2 = name->name;
	len2 = name->len;
	dsize1 = dsize2 = 0;
	dstr1 = dstr2 = NULL;

	while (len1 > 0 && len2 > 0) {
		if (!dsize1) {
			size = asc2unichar(sb, astr1, len1, &c);
			astr1 += size;
			len1 -= size;

			if (decompose)
				dstr1 = decompose_unichar(c, &dsize1,
							  dhangul_1);
			if (!decompose || !dstr1) {
				c1 = c;
				dstr1 = &c1;
				dsize1 = 1;
			}
		}

		if (!dsize2) {
			size = asc2unichar(sb, astr2, len2, &c);
			astr2 += size;
			len2 -= size;

			if (decompose)
				dstr2 = decompose_unichar(c, &dsize2,
							  dhangul_2);
			if (!decompose || !dstr2) {
				c2 = c;
				dstr2 = &c2;
				dsize2 = 1;
			}
		}

		c1 = *dstr1;
		c2 = *dstr2;
		if (casefold) {
			c1 = case_fold(c1);
			if (!c1) {
				dstr1++;
				dsize1--;
				continue;
			}
			c2 = case_fold(c2);
			if (!c2) {
				dstr2++;
				dsize2--;
				continue;
			}
		}
		if (c1 < c2)
			return -1;
		else if (c1 > c2)
			return 1;

		dstr1++;
		dsize1--;
		dstr2++;
		dsize2--;
	}

	if (len1 < len2)
		return -1;
	if (len1 > len2)
		return 1;
	return 0;
}