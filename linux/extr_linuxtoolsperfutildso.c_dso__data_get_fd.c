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
struct machine {int dummy; } ;
struct TYPE_2__ {scalar_t__ status; scalar_t__ fd; } ;
struct dso {TYPE_1__ data; } ;

/* Variables and functions */
 scalar_t__ DSO_DATA_STATUS_ERROR ; 
 int /*<<< orphan*/  dso__data_open_lock ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_to_open_dso (struct dso*,struct machine*) ; 

int dso__data_get_fd(struct dso *dso, struct machine *machine)
{
	if (dso->data.status == DSO_DATA_STATUS_ERROR)
		return -1;

	if (pthread_mutex_lock(&dso__data_open_lock) < 0)
		return -1;

	try_to_open_dso(dso, machine);

	if (dso->data.fd < 0)
		pthread_mutex_unlock(&dso__data_open_lock);

	return dso->data.fd;
}