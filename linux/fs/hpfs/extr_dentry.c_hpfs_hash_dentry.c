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
struct qstr {unsigned int len; char* name; int /*<<< orphan*/  hash; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  sb_cp_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  end_name_hash (unsigned long) ; 
 int /*<<< orphan*/  hpfs_adjust_length (char*,unsigned int*) ; 
 TYPE_1__* hpfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_upcase (int /*<<< orphan*/ ,char) ; 
 unsigned long init_name_hash (struct dentry const*) ; 
 unsigned long partial_name_hash (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int hpfs_hash_dentry(const struct dentry *dentry, struct qstr *qstr)
{
	unsigned long	 hash;
	int		 i;
	unsigned l = qstr->len;

	if (l == 1) if (qstr->name[0]=='.') goto x;
	if (l == 2) if (qstr->name[0]=='.' || qstr->name[1]=='.') goto x;
	hpfs_adjust_length(qstr->name, &l);
	/*if (hpfs_chk_name(qstr->name,&l))*/
		/*return -ENAMETOOLONG;*/
		/*return -ENOENT;*/
	x:

	hash = init_name_hash(dentry);
	for (i = 0; i < l; i++)
		hash = partial_name_hash(hpfs_upcase(hpfs_sb(dentry->d_sb)->sb_cp_table,qstr->name[i]), hash);
	qstr->hash = end_name_hash(hash);

	return 0;
}