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
struct TYPE_3__ {int /*<<< orphan*/ * next_sampler; } ;
typedef  TYPE_1__ gs_sparam_t ;
typedef  int /*<<< orphan*/  gs_samplerstate_t ;

/* Variables and functions */

void gs_shader_set_next_sampler(gs_sparam_t *param, gs_samplerstate_t *sampler)
{
	param->next_sampler = sampler;
}