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
struct TYPE_2__ {int /*<<< orphan*/  inflight_conn_req; struct pvcalls_data_intf* ring; } ;
struct sock_mapping {TYPE_1__ active; } ;
struct pvcalls_data_intf {scalar_t__ out_error; scalar_t__ in_error; } ;
struct pvcalls_bedata {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  scalar_t__ int32_t ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pvcalls_front_read_todo (struct sock_mapping*) ; 
 scalar_t__ pvcalls_front_write_todo (struct sock_mapping*) ; 

__attribute__((used)) static __poll_t pvcalls_front_poll_active(struct file *file,
					      struct pvcalls_bedata *bedata,
					      struct sock_mapping *map,
					      poll_table *wait)
{
	__poll_t mask = 0;
	int32_t in_error, out_error;
	struct pvcalls_data_intf *intf = map->active.ring;

	out_error = intf->out_error;
	in_error = intf->in_error;

	poll_wait(file, &map->active.inflight_conn_req, wait);
	if (pvcalls_front_write_todo(map))
		mask |= EPOLLOUT | EPOLLWRNORM;
	if (pvcalls_front_read_todo(map))
		mask |= EPOLLIN | EPOLLRDNORM;
	if (in_error != 0 || out_error != 0)
		mask |= EPOLLERR;

	return mask;
}