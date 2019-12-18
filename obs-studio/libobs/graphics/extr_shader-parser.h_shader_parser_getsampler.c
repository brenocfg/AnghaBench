#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct shader_sampler {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {size_t num; struct shader_sampler* array; } ;
struct shader_parser {TYPE_1__ samplers; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline struct shader_sampler *
shader_parser_getsampler(struct shader_parser *sp, const char *sampler_name)
{
	size_t i;
	for (i = 0; i < sp->samplers.num; i++) {
		struct shader_sampler *sampler = sp->samplers.array + i;
		if (strcmp(sampler->name, sampler_name) == 0)
			return sampler;
	}

	return NULL;
}