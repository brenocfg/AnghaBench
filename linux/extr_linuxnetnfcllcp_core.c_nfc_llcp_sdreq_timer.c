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
struct nfc_llcp_local {int /*<<< orphan*/  sdreq_timeout_work; } ;

/* Variables and functions */
 struct nfc_llcp_local* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct nfc_llcp_local* local ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdreq_timer ; 

__attribute__((used)) static void nfc_llcp_sdreq_timer(struct timer_list *t)
{
	struct nfc_llcp_local *local = from_timer(local, t, sdreq_timer);

	schedule_work(&local->sdreq_timeout_work);
}