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
struct fnic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fip_timer ; 
 struct fnic* fnic ; 
 int /*<<< orphan*/  fnic_handle_fip_timer (struct fnic*) ; 
 struct fnic* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fnic_fip_notify_timer(struct timer_list *t)
{
	struct fnic *fnic = from_timer(fnic, t, fip_timer);

	fnic_handle_fip_timer(fnic);
}