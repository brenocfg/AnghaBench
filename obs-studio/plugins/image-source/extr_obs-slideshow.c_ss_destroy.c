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
struct TYPE_2__ {int /*<<< orphan*/  da; } ;
struct slideshow {int /*<<< orphan*/  mutex; TYPE_1__ files; int /*<<< orphan*/  transition; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct slideshow*) ; 
 int /*<<< orphan*/  free_files (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ss_destroy(void *data)
{
	struct slideshow *ss = data;

	obs_source_release(ss->transition);
	free_files(&ss->files.da);
	pthread_mutex_destroy(&ss->mutex);
	bfree(ss);
}