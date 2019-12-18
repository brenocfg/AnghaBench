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
struct TYPE_2__ {size_t num; scalar_t__ array; } ;
struct macro_params {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  macro_param_free (scalar_t__) ; 

__attribute__((used)) static inline void macro_params_free(struct macro_params *params)
{
	size_t i;
	for (i = 0; i < params->params.num; i++)
		macro_param_free(params->params.array + i);
	da_free(params->params);
}