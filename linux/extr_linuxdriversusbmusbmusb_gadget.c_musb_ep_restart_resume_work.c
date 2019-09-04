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
struct musb_request {int dummy; } ;
struct musb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  musb_ep_restart (struct musb*,struct musb_request*) ; 

__attribute__((used)) static int musb_ep_restart_resume_work(struct musb *musb, void *data)
{
	struct musb_request *req = data;

	musb_ep_restart(musb, req);

	return 0;
}