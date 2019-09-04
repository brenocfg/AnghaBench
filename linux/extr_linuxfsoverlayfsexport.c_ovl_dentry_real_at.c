#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ovl_entry {int numlower; TYPE_2__* lowerstack; } ;
struct dentry {struct ovl_entry* d_fsdata; } ;
struct TYPE_4__ {struct dentry* dentry; TYPE_1__* layer; } ;
struct TYPE_3__ {int idx; } ;

/* Variables and functions */
 struct dentry* ovl_dentry_upper (struct dentry*) ; 

__attribute__((used)) static struct dentry *ovl_dentry_real_at(struct dentry *dentry, int idx)
{
	struct ovl_entry *oe = dentry->d_fsdata;
	int i;

	if (!idx)
		return ovl_dentry_upper(dentry);

	for (i = 0; i < oe->numlower; i++) {
		if (oe->lowerstack[i].layer->idx == idx)
			return oe->lowerstack[i].dentry;
	}

	return NULL;
}