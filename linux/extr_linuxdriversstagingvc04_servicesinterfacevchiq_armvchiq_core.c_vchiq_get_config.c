#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_INSTANCE_T ;
struct TYPE_5__ {int /*<<< orphan*/  version_min; int /*<<< orphan*/  version; int /*<<< orphan*/  max_services; int /*<<< orphan*/  max_outstanding_bulks; void* bulk_threshold; void* max_msg_size; } ;
typedef  TYPE_1__ VCHIQ_CONFIG_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCHIQ_ERROR ; 
 void* VCHIQ_MAX_MSG_SIZE ; 
 int /*<<< orphan*/  VCHIQ_MAX_SERVICES ; 
 int /*<<< orphan*/  VCHIQ_NUM_SERVICE_BULKS ; 
 int /*<<< orphan*/  VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  VCHIQ_VERSION ; 
 int /*<<< orphan*/  VCHIQ_VERSION_MIN ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 

VCHIQ_STATUS_T
vchiq_get_config(VCHIQ_INSTANCE_T instance,
	int config_size, VCHIQ_CONFIG_T *pconfig)
{
	VCHIQ_CONFIG_T config;

	(void)instance;

	config.max_msg_size           = VCHIQ_MAX_MSG_SIZE;
	config.bulk_threshold         = VCHIQ_MAX_MSG_SIZE;
	config.max_outstanding_bulks  = VCHIQ_NUM_SERVICE_BULKS;
	config.max_services           = VCHIQ_MAX_SERVICES;
	config.version                = VCHIQ_VERSION;
	config.version_min            = VCHIQ_VERSION_MIN;

	if (config_size > sizeof(VCHIQ_CONFIG_T))
		return VCHIQ_ERROR;

	memcpy(pconfig, &config,
		min(config_size, (int)(sizeof(VCHIQ_CONFIG_T))));

	return VCHIQ_SUCCESS;
}