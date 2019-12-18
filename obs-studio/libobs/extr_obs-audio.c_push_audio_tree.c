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
struct obs_core_audio {int /*<<< orphan*/  render_order; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 scalar_t__ DARRAY_INVALID ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 scalar_t__ da_find (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * obs_source_get_ref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void push_audio_tree(obs_source_t *parent, obs_source_t *source, void *p)
{
	struct obs_core_audio *audio = p;

	if (da_find(audio->render_order, &source, 0) == DARRAY_INVALID) {
		obs_source_t *s = obs_source_get_ref(source);
		if (s)
			da_push_back(audio->render_order, &s);
	}

	UNUSED_PARAMETER(parent);
}