#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gs_effect {int cached; struct gs_effect* next; scalar_t__ effect_path; TYPE_2__* graphics; } ;
struct TYPE_3__ {int /*<<< orphan*/  error_list; } ;
struct effect_parser {TYPE_1__ cfp; } ;
typedef  struct gs_effect gs_effect_t ;
struct TYPE_4__ {int /*<<< orphan*/  effect_mutex; struct gs_effect* first_effect; } ;

/* Variables and functions */
 scalar_t__ bstrdup (char const*) ; 
 struct gs_effect* bzalloc (int) ; 
 int /*<<< orphan*/  ep_free (struct effect_parser*) ; 
 int /*<<< orphan*/  ep_init (struct effect_parser*) ; 
 int ep_parse (struct effect_parser*,struct gs_effect*,char const*,char const*) ; 
 char* error_data_buildstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_effect_destroy (struct gs_effect*) ; 
 int /*<<< orphan*/  gs_valid_p (char*,char const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* thread_graphics ; 

gs_effect_t *gs_effect_create(const char *effect_string, const char *filename,
			      char **error_string)
{
	if (!gs_valid_p("gs_effect_create", effect_string))
		return NULL;

	struct gs_effect *effect = bzalloc(sizeof(struct gs_effect));
	struct effect_parser parser;
	bool success;

	effect->graphics = thread_graphics;
	effect->effect_path = bstrdup(filename);

	ep_init(&parser);
	success = ep_parse(&parser, effect, effect_string, filename);
	if (!success) {
		if (error_string)
			*error_string =
				error_data_buildstring(&parser.cfp.error_list);
		gs_effect_destroy(effect);
		effect = NULL;
	}

	if (effect) {
		pthread_mutex_lock(&thread_graphics->effect_mutex);

		if (effect->effect_path) {
			effect->cached = true;
			effect->next = thread_graphics->first_effect;
			thread_graphics->first_effect = effect;
		}

		pthread_mutex_unlock(&thread_graphics->effect_mutex);
	}

	ep_free(&parser);
	return effect;
}