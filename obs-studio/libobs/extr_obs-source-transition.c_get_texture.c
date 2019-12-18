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
struct TYPE_3__ {int /*<<< orphan*/ * transition_texrender; } ;
typedef  TYPE_1__ obs_source_t ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  enum obs_transition_target { ____Placeholder_obs_transition_target } obs_transition_target ;

/* Variables and functions */
 int /*<<< orphan*/ * gs_texrender_get_texture (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline gs_texture_t *get_texture(obs_source_t *transition,
					enum obs_transition_target target)
{
	size_t idx = (size_t)target;
	return gs_texrender_get_texture(transition->transition_texrender[idx]);
}