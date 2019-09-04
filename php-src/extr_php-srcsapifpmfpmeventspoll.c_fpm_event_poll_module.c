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
struct fpm_event_module_s {int dummy; } ;

/* Variables and functions */

struct fpm_event_module_s *fpm_event_poll_module() /* {{{ */
{
#if HAVE_POLL
	return &poll_module;
#else
	return NULL;
#endif /* HAVE_POLL */
}