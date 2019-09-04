#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timer_list {int dummy; } ;
struct ibmvfc_host {int /*<<< orphan*/  dev; } ;
struct ibmvfc_event {struct ibmvfc_host* vhost; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct ibmvfc_event*) ; 
 struct ibmvfc_event* evt ; 
 struct ibmvfc_event* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_reset_host (struct ibmvfc_host*) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void ibmvfc_timeout(struct timer_list *t)
{
	struct ibmvfc_event *evt = from_timer(evt, t, timer);
	struct ibmvfc_host *vhost = evt->vhost;
	dev_err(vhost->dev, "Command timed out (%p). Resetting connection\n", evt);
	ibmvfc_reset_host(vhost);
}