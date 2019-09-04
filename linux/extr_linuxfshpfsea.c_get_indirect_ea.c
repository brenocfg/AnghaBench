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
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  secno ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ hpfs_ea_read (struct super_block*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static char *get_indirect_ea(struct super_block *s, int ano, secno a, int size)
{
	char *ret;
	if (!(ret = kmalloc(size + 1, GFP_NOFS))) {
		pr_err("out of memory for EA\n");
		return NULL;
	}
	if (hpfs_ea_read(s, a, ano, 0, size, ret)) {
		kfree(ret);
		return NULL;
	}
	ret[size] = 0;
	return ret;
}