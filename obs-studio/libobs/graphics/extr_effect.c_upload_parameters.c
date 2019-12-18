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
struct gs_effect {TYPE_3__* cur_pass; } ;
struct darray {int dummy; } ;
struct TYPE_5__ {struct darray da; } ;
struct TYPE_4__ {struct darray da; } ;
struct TYPE_6__ {TYPE_2__ pixelshader_params; TYPE_1__ vertshader_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  reset_params (struct darray*) ; 
 int /*<<< orphan*/  upload_shader_params (struct darray*,int) ; 

__attribute__((used)) static inline void upload_parameters(struct gs_effect *effect,
				     bool changed_only)
{
	struct darray *vshader_params, *pshader_params;

	if (!effect->cur_pass)
		return;

	vshader_params = &effect->cur_pass->vertshader_params.da;
	pshader_params = &effect->cur_pass->pixelshader_params.da;

	upload_shader_params(vshader_params, changed_only);
	upload_shader_params(pshader_params, changed_only);
	reset_params(vshader_params);
	reset_params(pshader_params);
}