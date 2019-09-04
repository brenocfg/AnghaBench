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
struct qstr {unsigned char* name; int /*<<< orphan*/  hash; } ;
struct nls_table {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {struct nls_table* nls_io; } ;

/* Variables and functions */
 TYPE_1__* MSDOS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_name_hash (unsigned long) ; 
 unsigned long init_name_hash (struct dentry const*) ; 
 int /*<<< orphan*/  nls_tolower (struct nls_table*,int /*<<< orphan*/ ) ; 
 unsigned long partial_name_hash (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned int vfat_striptail_len (struct qstr*) ; 

__attribute__((used)) static int vfat_hashi(const struct dentry *dentry, struct qstr *qstr)
{
	struct nls_table *t = MSDOS_SB(dentry->d_sb)->nls_io;
	const unsigned char *name;
	unsigned int len;
	unsigned long hash;

	name = qstr->name;
	len = vfat_striptail_len(qstr);

	hash = init_name_hash(dentry);
	while (len--)
		hash = partial_name_hash(nls_tolower(t, *name++), hash);
	qstr->hash = end_name_hash(hash);

	return 0;
}