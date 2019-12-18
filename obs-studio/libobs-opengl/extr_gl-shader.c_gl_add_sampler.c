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
struct shader_sampler {int dummy; } ;
struct gs_shader {int /*<<< orphan*/  samplers; int /*<<< orphan*/  device; } ;
struct gs_sampler_info {int dummy; } ;
typedef  int /*<<< orphan*/  gs_samplerstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * device_samplerstate_create (int /*<<< orphan*/ ,struct gs_sampler_info*) ; 
 int /*<<< orphan*/  shader_sampler_convert (struct shader_sampler*,struct gs_sampler_info*) ; 

__attribute__((used)) static inline void gl_add_sampler(struct gs_shader *shader,
				  struct shader_sampler *sampler)
{
	gs_samplerstate_t *new_sampler;
	struct gs_sampler_info info;

	shader_sampler_convert(sampler, &info);
	new_sampler = device_samplerstate_create(shader->device, &info);

	da_push_back(shader->samplers, &new_sampler);
}