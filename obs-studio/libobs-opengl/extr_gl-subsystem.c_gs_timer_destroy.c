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
struct TYPE_4__ {int /*<<< orphan*/  queries; } ;
typedef  TYPE_1__ gs_timer_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  glDeleteQueries (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

void gs_timer_destroy(gs_timer_t *timer)
{
	if (!timer)
		return;

	glDeleteQueries(2, timer->queries);
	gl_success("glDeleteQueries");

	bfree(timer);
}