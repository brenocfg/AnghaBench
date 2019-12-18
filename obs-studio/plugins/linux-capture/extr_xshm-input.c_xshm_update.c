#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  obs_data_t ;
struct TYPE_4__ {int /*<<< orphan*/  server; void* advanced; void* show_cursor; int /*<<< orphan*/  screen_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSHM_DATA (void*) ; 
 int /*<<< orphan*/  bstrdup (int /*<<< orphan*/ ) ; 
 TYPE_1__* data ; 
 void* obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xshm_capture_start (TYPE_1__*) ; 
 int /*<<< orphan*/  xshm_capture_stop (TYPE_1__*) ; 

__attribute__((used)) static void xshm_update(void *vptr, obs_data_t *settings)
{
	XSHM_DATA(vptr);

	xshm_capture_stop(data);

	data->screen_id = obs_data_get_int(settings, "screen");
	data->show_cursor = obs_data_get_bool(settings, "show_cursor");
	data->advanced = obs_data_get_bool(settings, "advanced");
	data->server = bstrdup(obs_data_get_string(settings, "server"));

	xshm_capture_start(data);
}