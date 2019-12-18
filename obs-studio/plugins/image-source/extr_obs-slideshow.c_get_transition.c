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
struct slideshow {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * transition; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_source_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static obs_source_t *get_transition(struct slideshow *ss)
{
	obs_source_t *tr;

	pthread_mutex_lock(&ss->mutex);
	tr = ss->transition;
	obs_source_addref(tr);
	pthread_mutex_unlock(&ss->mutex);

	return tr;
}