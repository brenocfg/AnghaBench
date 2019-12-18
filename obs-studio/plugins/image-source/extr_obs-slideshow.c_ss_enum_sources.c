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
struct slideshow {int /*<<< orphan*/  mutex; scalar_t__ transition; int /*<<< orphan*/  source; } ;
typedef  int /*<<< orphan*/  (* obs_source_enum_proc_t ) (int /*<<< orphan*/ ,scalar_t__,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ss_enum_sources(void *data, obs_source_enum_proc_t cb, void *param)
{
	struct slideshow *ss = data;

	pthread_mutex_lock(&ss->mutex);
	if (ss->transition)
		cb(ss->source, ss->transition, param);
	pthread_mutex_unlock(&ss->mutex);
}