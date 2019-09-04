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
struct flv_output {int /*<<< orphan*/  path; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct flv_output*) ; 
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flv_output_destroy(void *data)
{
	struct flv_output *stream = data;

	pthread_mutex_destroy(&stream->mutex);
	dstr_free(&stream->path);
	bfree(stream);
}