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
struct gs_timer {void** queries; } ;
typedef  struct gs_timer gs_timer_t ;
typedef  int /*<<< orphan*/  gs_device_t ;
typedef  void* GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 struct gs_timer* bzalloc (int) ; 
 int /*<<< orphan*/  glGenQueries (int,void**) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

gs_timer_t *device_timer_create(gs_device_t *device)
{
	UNUSED_PARAMETER(device);

	struct gs_timer *timer;

	GLuint queries[2];
	glGenQueries(2, queries);
	if (!gl_success("glGenQueries"))
		return NULL;

	timer = bzalloc(sizeof(struct gs_timer));
	timer->queries[0] = queries[0];
	timer->queries[1] = queries[1];

	return timer;
}