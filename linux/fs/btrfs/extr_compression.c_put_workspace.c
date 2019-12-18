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
struct list_head {int dummy; } ;
struct TYPE_2__ {void (* put_workspace ) (struct list_head*) ;} ;

/* Variables and functions */
 TYPE_1__** btrfs_compress_op ; 
 void stub1 (struct list_head*) ; 

__attribute__((used)) static void put_workspace(int type, struct list_head *ws)
{
	return btrfs_compress_op[type]->put_workspace(ws);
}