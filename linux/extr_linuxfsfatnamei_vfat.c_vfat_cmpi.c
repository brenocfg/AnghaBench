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
struct qstr {int /*<<< orphan*/  name; } ;
struct nls_table {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {struct nls_table* nls_io; } ;

/* Variables and functions */
 TYPE_1__* MSDOS_SB (int /*<<< orphan*/ ) ; 
 unsigned int __vfat_striptail_len (unsigned int,char const*) ; 
 scalar_t__ nls_strnicmp (struct nls_table*,int /*<<< orphan*/ ,char const*,unsigned int) ; 
 unsigned int vfat_striptail_len (struct qstr const*) ; 

__attribute__((used)) static int vfat_cmpi(const struct dentry *dentry,
		unsigned int len, const char *str, const struct qstr *name)
{
	struct nls_table *t = MSDOS_SB(dentry->d_sb)->nls_io;
	unsigned int alen, blen;

	/* A filename cannot end in '.' or we treat it like it has none */
	alen = vfat_striptail_len(name);
	blen = __vfat_striptail_len(len, str);
	if (alen == blen) {
		if (nls_strnicmp(t, name->name, str, alen) == 0)
			return 0;
	}
	return 1;
}