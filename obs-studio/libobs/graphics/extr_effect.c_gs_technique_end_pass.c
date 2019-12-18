#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  da; } ;
struct TYPE_6__ {int /*<<< orphan*/  da; } ;
struct gs_effect_pass {TYPE_2__ pixelshader_params; TYPE_1__ vertshader_params; } ;
struct TYPE_9__ {TYPE_3__* effect; } ;
typedef  TYPE_4__ gs_technique_t ;
struct TYPE_8__ {struct gs_effect_pass* cur_pass; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_tex_params (int /*<<< orphan*/ *) ; 

void gs_technique_end_pass(gs_technique_t *tech)
{
	if (!tech)
		return;

	struct gs_effect_pass *pass = tech->effect->cur_pass;
	if (!pass)
		return;

	clear_tex_params(&pass->vertshader_params.da);
	clear_tex_params(&pass->pixelshader_params.da);
	tech->effect->cur_pass = NULL;
}