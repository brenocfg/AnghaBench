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
struct dwc3_request {int started; int /*<<< orphan*/  list; struct dwc3_ep* dep; } ;
struct dwc3_ep {int /*<<< orphan*/  started_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dwc3_gadget_move_started_request(struct dwc3_request *req)
{
	struct dwc3_ep		*dep = req->dep;

	req->started = true;
	list_move_tail(&req->list, &dep->started_list);
}