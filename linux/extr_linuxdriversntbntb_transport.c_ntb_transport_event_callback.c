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
struct ntb_transport_ctx {int /*<<< orphan*/  link_cleanup; int /*<<< orphan*/  link_work; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int ntb_link_is_up (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ntb_transport_event_callback(void *data)
{
	struct ntb_transport_ctx *nt = data;

	if (ntb_link_is_up(nt->ndev, NULL, NULL) == 1)
		schedule_delayed_work(&nt->link_work, 0);
	else
		schedule_work(&nt->link_cleanup);
}