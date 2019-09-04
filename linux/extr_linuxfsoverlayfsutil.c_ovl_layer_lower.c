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
struct ovl_layer {int dummy; } ;
struct ovl_entry {TYPE_1__* lowerstack; scalar_t__ numlower; } ;
struct dentry {struct ovl_entry* d_fsdata; } ;
struct TYPE_2__ {struct ovl_layer* layer; } ;

/* Variables and functions */

struct ovl_layer *ovl_layer_lower(struct dentry *dentry)
{
	struct ovl_entry *oe = dentry->d_fsdata;

	return oe->numlower ? oe->lowerstack[0].layer : NULL;
}