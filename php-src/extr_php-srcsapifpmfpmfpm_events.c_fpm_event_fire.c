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
struct fpm_event_s {int /*<<< orphan*/  arg; int /*<<< orphan*/  which; int /*<<< orphan*/  (* callback ) (struct fpm_event_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct fpm_event_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fpm_event_fire(struct fpm_event_s *ev) /* {{{ */
{
	if (!ev || !ev->callback) {
		return;
	}

	(*ev->callback)( (struct fpm_event_s *) ev, ev->which, ev->arg);
}