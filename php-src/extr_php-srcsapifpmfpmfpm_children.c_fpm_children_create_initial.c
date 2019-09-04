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
struct fpm_worker_pool_s {int socket_event_set; struct fpm_event_s* ondemand_event; int /*<<< orphan*/  listening_socket; TYPE_1__* config; } ;
struct fpm_event_s {int dummy; } ;
struct TYPE_2__ {scalar_t__ pm; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int FPM_EV_EDGE ; 
 int FPM_EV_READ ; 
 scalar_t__ PM_STYLE_ONDEMAND ; 
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int fpm_children_make (struct fpm_worker_pool_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fpm_event_add (struct fpm_event_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_event_set (struct fpm_event_s*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct fpm_worker_pool_s*) ; 
 int /*<<< orphan*/  fpm_pctl_on_socket_accept ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct fpm_event_s*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int fpm_children_create_initial(struct fpm_worker_pool_s *wp) /* {{{ */
{
	if (wp->config->pm == PM_STYLE_ONDEMAND) {
		wp->ondemand_event = (struct fpm_event_s *)malloc(sizeof(struct fpm_event_s));

		if (!wp->ondemand_event) {
			zlog(ZLOG_ERROR, "[pool %s] unable to malloc the ondemand socket event", wp->config->name);
			// FIXME handle crash
			return 1;
		}

		memset(wp->ondemand_event, 0, sizeof(struct fpm_event_s));
		fpm_event_set(wp->ondemand_event, wp->listening_socket, FPM_EV_READ | FPM_EV_EDGE, fpm_pctl_on_socket_accept, wp);
		wp->socket_event_set = 1;
		fpm_event_add(wp->ondemand_event, 0);

		return 1;
	}
	return fpm_children_make(wp, 0 /* not in event loop yet */, 0, 1);
}