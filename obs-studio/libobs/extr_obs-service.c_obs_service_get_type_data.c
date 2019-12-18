#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* type_data; } ;
struct TYPE_6__ {TYPE_1__ info; } ;
typedef  TYPE_2__ obs_service_t ;

/* Variables and functions */
 scalar_t__ obs_service_valid (TYPE_2__*,char*) ; 

void *obs_service_get_type_data(obs_service_t *service)
{
	return obs_service_valid(service, "obs_service_get_type_data")
		       ? service->info.type_data
		       : NULL;
}