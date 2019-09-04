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
struct sg_timeout {int /*<<< orphan*/  req; } ;

/* Variables and functions */
 struct sg_timeout* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct sg_timeout* timeout ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  usb_sg_cancel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sg_timeout(struct timer_list *t)
{
	struct sg_timeout *timeout = from_timer(timeout, t, timer);

	usb_sg_cancel(timeout->req);
}