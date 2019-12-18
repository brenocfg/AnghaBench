#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/ * queries; } ;
typedef  TYPE_1__ gs_timer_t ;
typedef  scalar_t__ GLuint64 ;
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_QUERY_RESULT ; 
 int /*<<< orphan*/  GL_QUERY_RESULT_AVAILABLE ; 
 int /*<<< orphan*/  glGetQueryObjectiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGetQueryObjectui64v (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

bool gs_timer_get_data(gs_timer_t *timer, uint64_t *ticks)
{
	GLint available = 0;
	glGetQueryObjectiv(timer->queries[1], GL_QUERY_RESULT_AVAILABLE,
			   &available);

	GLuint64 begin, end;
	glGetQueryObjectui64v(timer->queries[0], GL_QUERY_RESULT, &begin);
	gl_success("glGetQueryObjectui64v");
	glGetQueryObjectui64v(timer->queries[1], GL_QUERY_RESULT, &end);
	gl_success("glGetQueryObjectui64v");

	*ticks = end - begin;
	return true;
}