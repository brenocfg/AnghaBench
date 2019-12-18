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
struct ovl_entry {int numlower; TYPE_1__* lowerstack; } ;
struct dentry {struct ovl_entry* d_fsdata; } ;
struct TYPE_2__ {struct dentry* dentry; } ;

/* Variables and functions */

struct dentry *ovl_dentry_lowerdata(struct dentry *dentry)
{
	struct ovl_entry *oe = dentry->d_fsdata;

	return oe->numlower ? oe->lowerstack[oe->numlower - 1].dentry : NULL;
}