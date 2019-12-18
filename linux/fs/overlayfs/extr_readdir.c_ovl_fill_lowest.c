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
typedef  int /*<<< orphan*/  u64 ;
struct ovl_readdir_data {int err; int /*<<< orphan*/  middle; int /*<<< orphan*/  root; } ;
struct ovl_cache_entry {int /*<<< orphan*/  l_node; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ovl_cache_entry* ovl_cache_entry_find (int /*<<< orphan*/ ,char const*,int) ; 
 struct ovl_cache_entry* ovl_cache_entry_new (struct ovl_readdir_data*,char const*,int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ovl_fill_lowest(struct ovl_readdir_data *rdd,
			   const char *name, int namelen,
			   loff_t offset, u64 ino, unsigned int d_type)
{
	struct ovl_cache_entry *p;

	p = ovl_cache_entry_find(rdd->root, name, namelen);
	if (p) {
		list_move_tail(&p->l_node, &rdd->middle);
	} else {
		p = ovl_cache_entry_new(rdd, name, namelen, ino, d_type);
		if (p == NULL)
			rdd->err = -ENOMEM;
		else
			list_add_tail(&p->l_node, &rdd->middle);
	}

	return rdd->err;
}