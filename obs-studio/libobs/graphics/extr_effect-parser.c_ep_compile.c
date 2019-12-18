#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t num; } ;
struct TYPE_4__ {size_t num; } ;
struct effect_parser {TYPE_2__ techniques; TYPE_1__ params; TYPE_3__* effect; } ;
struct TYPE_6__ {int /*<<< orphan*/  techniques; int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  da_resize (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ep_compile_param (struct effect_parser*,size_t) ; 
 int /*<<< orphan*/  ep_compile_technique (struct effect_parser*,size_t) ; 

__attribute__((used)) static bool ep_compile(struct effect_parser *ep)
{
	bool success = true;
	size_t i;

	assert(ep->effect);

	da_resize(ep->effect->params, ep->params.num);
	da_resize(ep->effect->techniques, ep->techniques.num);

#if defined(_DEBUG) && defined(_DEBUG_SHADERS)
	blog(LOG_DEBUG, "Shader has %lld parameters:", ep->params.num);
#endif

	for (i = 0; i < ep->params.num; i++)
		ep_compile_param(ep, i);

#if defined(_DEBUG) && defined(_DEBUG_SHADERS)
	blog(LOG_DEBUG, "Shader has %lld techniques:", ep->techniques.num);
#endif

	for (i = 0; i < ep->techniques.num; i++) {
		if (!ep_compile_technique(ep, i))
			success = false;
	}

	return success;
}