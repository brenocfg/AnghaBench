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

/* Variables and functions */
 int /*<<< orphan*/  fpm_event_queue_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpm_event_queue_fd ; 
 int /*<<< orphan*/  fpm_event_queue_timer ; 

__attribute__((used)) static void fpm_event_cleanup(int which, void *arg) /* {{{ */
{
	fpm_event_queue_destroy(&fpm_event_queue_timer);
	fpm_event_queue_destroy(&fpm_event_queue_fd);
}