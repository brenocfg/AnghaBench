#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {char const* (* get_key ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_2__ context; TYPE_1__ info; } ;
typedef  TYPE_3__ obs_service_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_service_valid (TYPE_3__ const*,char*) ; 
 char const* stub1 (int /*<<< orphan*/ ) ; 

const char *obs_service_get_key(const obs_service_t *service)
{
	if (!obs_service_valid(service, "obs_service_get_key"))
		return NULL;

	if (!service->info.get_key)
		return NULL;
	return service->info.get_key(service->context.data);
}