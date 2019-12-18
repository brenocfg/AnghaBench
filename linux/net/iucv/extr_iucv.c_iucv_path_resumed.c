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
struct iucv_path_resumed {size_t ippathid; int /*<<< orphan*/  ipuser; } ;
struct iucv_path {TYPE_1__* handler; } ;
struct iucv_irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* path_resumed ) (struct iucv_path*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct iucv_path** iucv_path_table ; 
 int /*<<< orphan*/  stub1 (struct iucv_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iucv_path_resumed(struct iucv_irq_data *data)
{
	struct iucv_path_resumed *ipr = (void *) data;
	struct iucv_path *path = iucv_path_table[ipr->ippathid];

	if (path && path->handler && path->handler->path_resumed)
		path->handler->path_resumed(path, ipr->ipuser);
}