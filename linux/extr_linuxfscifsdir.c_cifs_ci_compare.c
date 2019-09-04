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
typedef  int /*<<< orphan*/  wchar_t ;
struct qstr {unsigned int len; char const* name; } ;
struct nls_table {int (* char2uni ) (char const*,unsigned int,int /*<<< orphan*/ *) ;} ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {struct nls_table* local_nls; } ;

/* Variables and functions */
 TYPE_1__* CIFS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ cifs_toupper (int /*<<< orphan*/ ) ; 
 int stub1 (char const*,unsigned int,int /*<<< orphan*/ *) ; 
 int stub2 (char const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cifs_ci_compare(const struct dentry *dentry,
		unsigned int len, const char *str, const struct qstr *name)
{
	struct nls_table *codepage = CIFS_SB(dentry->d_sb)->local_nls;
	wchar_t c1, c2;
	int i, l1, l2;

	/*
	 * We make the assumption here that uppercase characters in the local
	 * codepage are always the same length as their lowercase counterparts.
	 *
	 * If that's ever not the case, then this will fail to match it.
	 */
	if (name->len != len)
		return 1;

	for (i = 0; i < len; i += l1) {
		/* Convert characters in both strings to UTF-16. */
		l1 = codepage->char2uni(&str[i], len - i, &c1);
		l2 = codepage->char2uni(&name->name[i], name->len - i, &c2);

		/*
		 * If we can't convert either character, just declare it to
		 * be 1 byte long and compare the original byte.
		 */
		if (unlikely(l1 < 0 && l2 < 0)) {
			if (str[i] != name->name[i])
				return 1;
			l1 = 1;
			continue;
		}

		/*
		 * Here, we again ass|u|me that upper/lowercase versions of
		 * a character are the same length in the local NLS.
		 */
		if (l1 != l2)
			return 1;

		/* Now compare uppercase versions of these characters */
		if (cifs_toupper(c1) != cifs_toupper(c2))
			return 1;
	}

	return 0;
}