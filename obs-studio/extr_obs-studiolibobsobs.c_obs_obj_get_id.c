#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct obs_context_data {int type; } ;
struct TYPE_9__ {char const* id; } ;
struct TYPE_13__ {TYPE_1__ info; } ;
typedef  TYPE_5__ obs_source_t ;
struct TYPE_12__ {char const* id; } ;
struct TYPE_14__ {TYPE_4__ info; } ;
typedef  TYPE_6__ obs_service_t ;
struct TYPE_10__ {char const* id; } ;
struct TYPE_15__ {TYPE_2__ info; } ;
typedef  TYPE_7__ obs_output_t ;
struct TYPE_11__ {char const* id; } ;
struct TYPE_16__ {TYPE_3__ info; } ;
typedef  TYPE_8__ obs_encoder_t ;

/* Variables and functions */
#define  OBS_OBJ_TYPE_ENCODER 131 
#define  OBS_OBJ_TYPE_OUTPUT 130 
#define  OBS_OBJ_TYPE_SERVICE 129 
#define  OBS_OBJ_TYPE_SOURCE 128 

const char *obs_obj_get_id(void *obj)
{
	struct obs_context_data *context = obj;
	if (!context)
		return NULL;

	switch (context->type) {
	case OBS_OBJ_TYPE_SOURCE:  return ((obs_source_t*)obj)->info.id;
	case OBS_OBJ_TYPE_OUTPUT:  return ((obs_output_t*)obj)->info.id;
	case OBS_OBJ_TYPE_ENCODER: return ((obs_encoder_t*)obj)->info.id;
	case OBS_OBJ_TYPE_SERVICE: return ((obs_service_t*)obj)->info.id;
	default:;
	}

	return NULL;
}