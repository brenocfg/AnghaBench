#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * transition_texrender; int /*<<< orphan*/  transition_tex_mutex; int /*<<< orphan*/  transition_mutex; } ;
typedef  TYPE_2__ obs_source_t ;
struct TYPE_5__ {int /*<<< orphan*/  graphics; } ;
struct TYPE_7__ {TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  gs_enter_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_leave_context () ; 
 int /*<<< orphan*/  gs_texrender_destroy (int /*<<< orphan*/ ) ; 
 TYPE_4__* obs ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void obs_transition_free(obs_source_t *transition)
{
	pthread_mutex_destroy(&transition->transition_mutex);
	pthread_mutex_destroy(&transition->transition_tex_mutex);

	gs_enter_context(obs->video.graphics);
	gs_texrender_destroy(transition->transition_texrender[0]);
	gs_texrender_destroy(transition->transition_texrender[1]);
	gs_leave_context();
}