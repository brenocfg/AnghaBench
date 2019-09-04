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
struct ovl_dir_cache {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct ovl_dir_cache* cache; } ;

/* Variables and functions */
 TYPE_1__* OVL_I (struct inode*) ; 

struct ovl_dir_cache *ovl_dir_cache(struct inode *inode)
{
	return OVL_I(inode)->cache;
}