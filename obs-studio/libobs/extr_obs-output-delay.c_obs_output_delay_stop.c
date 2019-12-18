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
struct delay_data {int /*<<< orphan*/  ts; int /*<<< orphan*/  msg; } ;
struct TYPE_4__ {int /*<<< orphan*/  delay_mutex; int /*<<< orphan*/  delay_data; } ;
typedef  TYPE_1__ obs_output_t ;
typedef  int /*<<< orphan*/  dd ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY_MSG_STOP ; 
 int /*<<< orphan*/  circlebuf_push_back (int /*<<< orphan*/ *,struct delay_data*,int) ; 
 int /*<<< orphan*/  do_output_signal (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  os_gettime_ns () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void obs_output_delay_stop(obs_output_t *output)
{
	struct delay_data dd = {
		.msg = DELAY_MSG_STOP,
		.ts = os_gettime_ns(),
	};

	pthread_mutex_lock(&output->delay_mutex);
	circlebuf_push_back(&output->delay_data, &dd, sizeof(dd));
	pthread_mutex_unlock(&output->delay_mutex);

	do_output_signal(output, "stopping");
}