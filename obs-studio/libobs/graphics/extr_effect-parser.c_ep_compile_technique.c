#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t num; } ;
struct gs_effect_technique {TYPE_5__ passes; int /*<<< orphan*/  name; TYPE_3__* effect; int /*<<< orphan*/  section; } ;
struct TYPE_9__ {int /*<<< orphan*/  num; } ;
struct ep_technique {TYPE_4__ passes; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {struct ep_technique* array; } ;
struct effect_parser {TYPE_3__* effect; TYPE_2__ techniques; } ;
struct TYPE_6__ {struct gs_effect_technique* array; } ;
struct TYPE_8__ {TYPE_1__ techniques; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFFECT_TECHNIQUE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  bstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_resize (TYPE_5__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep_compile_pass (struct effect_parser*,struct gs_effect_technique*,struct ep_technique*,size_t) ; 

__attribute__((used)) static inline bool ep_compile_technique(struct effect_parser *ep, size_t idx)
{
	struct gs_effect_technique *tech;
	struct ep_technique *tech_in;
	bool success = true;
	size_t i;

	tech = ep->effect->techniques.array + idx;
	tech_in = ep->techniques.array + idx;

	tech->name = bstrdup(tech_in->name);
	tech->section = EFFECT_TECHNIQUE;
	tech->effect = ep->effect;

	da_resize(tech->passes, tech_in->passes.num);

#if defined(_DEBUG) && defined(_DEBUG_SHADERS)
	blog(LOG_DEBUG, "\t[%4lld] Technique '%s' has %lld passes:", idx,
	     tech->name, tech->passes.num);
#endif

	for (i = 0; i < tech->passes.num; i++) {
		if (!ep_compile_pass(ep, tech, tech_in, i))
			success = false;
	}

	return success;
}