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
struct nfc_llcp_local {int /*<<< orphan*/  timeout_work; } ;

/* Variables and functions */
 struct nfc_llcp_local* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_timer ; 
 struct nfc_llcp_local* local ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfc_llcp_symm_timer(struct timer_list *t)
{
	struct nfc_llcp_local *local = from_timer(local, t, link_timer);

	pr_err("SYMM timeout\n");

	schedule_work(&local->timeout_work);
}