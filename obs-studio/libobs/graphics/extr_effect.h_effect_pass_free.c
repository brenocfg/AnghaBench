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
struct gs_effect_pass {int /*<<< orphan*/  pixelshader; int /*<<< orphan*/  vertshader; int /*<<< orphan*/  pixelshader_params; int /*<<< orphan*/  vertshader_params; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_shader_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void effect_pass_free(struct gs_effect_pass *pass)
{
	bfree(pass->name);
	da_free(pass->vertshader_params);
	da_free(pass->pixelshader_params);

	gs_shader_destroy(pass->vertshader);
	gs_shader_destroy(pass->pixelshader);
}