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
struct iucv_path_severed {size_t ippathid; int /*<<< orphan*/  ipuser; } ;
struct iucv_path {size_t pathid; int /*<<< orphan*/  list; TYPE_1__* handler; } ;
struct iucv_irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* path_severed ) (struct iucv_path*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  iucv_path_free (struct iucv_path*) ; 
 struct iucv_path** iucv_path_table ; 
 int /*<<< orphan*/  iucv_sever_pathid (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct iucv_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iucv_path_severed(struct iucv_irq_data *data)
{
	struct iucv_path_severed *ips = (void *) data;
	struct iucv_path *path = iucv_path_table[ips->ippathid];

	if (!path || !path->handler)	/* Already severed */
		return;
	if (path->handler->path_severed)
		path->handler->path_severed(path, ips->ipuser);
	else {
		iucv_sever_pathid(path->pathid, NULL);
		iucv_path_table[path->pathid] = NULL;
		list_del(&path->list);
		iucv_path_free(path);
	}
}