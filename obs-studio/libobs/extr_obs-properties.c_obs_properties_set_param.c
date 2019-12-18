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
struct TYPE_3__ {void* param; void (* destroy ) (void*) ;} ;
typedef  TYPE_1__ obs_properties_t ;

/* Variables and functions */
 void stub1 (void*) ; 

void obs_properties_set_param(obs_properties_t *props, void *param,
			      void (*destroy)(void *param))
{
	if (!props)
		return;

	if (props->param && props->destroy)
		props->destroy(props->param);

	props->param = param;
	props->destroy = destroy;
}