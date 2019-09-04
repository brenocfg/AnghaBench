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
struct resv_map {int dummy; } ;
struct inode {TYPE_1__* i_mapping; } ;
struct TYPE_2__ {struct resv_map* private_data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct resv_map *inode_resv_map(struct inode *inode)
{
	return inode->i_mapping->private_data;
}