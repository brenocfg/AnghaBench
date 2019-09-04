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
struct TYPE_2__ {scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct zfcp_fsf_req {TYPE_1__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  zfcp_fsf_request_timeout_handler ; 

__attribute__((used)) static void zfcp_fsf_start_timer(struct zfcp_fsf_req *fsf_req,
				 unsigned long timeout)
{
	fsf_req->timer.function = zfcp_fsf_request_timeout_handler;
	fsf_req->timer.expires = jiffies + timeout;
	add_timer(&fsf_req->timer);
}