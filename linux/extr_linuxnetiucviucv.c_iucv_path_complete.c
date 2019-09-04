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
struct iucv_path_complete {size_t ippathid; int /*<<< orphan*/  ipuser; int /*<<< orphan*/  ipflags1; } ;
struct iucv_path {TYPE_1__* handler; int /*<<< orphan*/  flags; } ;
struct iucv_irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* path_complete ) (struct iucv_path*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct iucv_path** iucv_path_table ; 
 int /*<<< orphan*/  stub1 (struct iucv_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iucv_path_complete(struct iucv_irq_data *data)
{
	struct iucv_path_complete *ipc = (void *) data;
	struct iucv_path *path = iucv_path_table[ipc->ippathid];

	if (path)
		path->flags = ipc->ipflags1;
	if (path && path->handler && path->handler->path_complete)
		path->handler->path_complete(path, ipc->ipuser);
}