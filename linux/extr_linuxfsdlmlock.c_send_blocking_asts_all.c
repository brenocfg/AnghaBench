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
struct dlm_rsb {int /*<<< orphan*/  res_convertqueue; int /*<<< orphan*/  res_grantqueue; } ;
struct dlm_lkb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  send_bast_queue (struct dlm_rsb*,int /*<<< orphan*/ *,struct dlm_lkb*) ; 

__attribute__((used)) static void send_blocking_asts_all(struct dlm_rsb *r, struct dlm_lkb *lkb)
{
	send_bast_queue(r, &r->res_grantqueue, lkb);
	send_bast_queue(r, &r->res_convertqueue, lkb);
}