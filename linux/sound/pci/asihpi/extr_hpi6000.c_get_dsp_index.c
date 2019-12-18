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
typedef  int u16 ;
struct hpi_message {int object; int obj_index; } ;
struct hpi_adapter_obj {int dummy; } ;

/* Variables and functions */
#define  HPI_OBJ_ISTREAM 129 
#define  HPI_OBJ_PROFILE 128 

__attribute__((used)) static u16 get_dsp_index(struct hpi_adapter_obj *pao, struct hpi_message *phm)
{
	u16 ret = 0;
	switch (phm->object) {
	case HPI_OBJ_ISTREAM:
		if (phm->obj_index < 2)
			ret = 1;
		break;
	case HPI_OBJ_PROFILE:
		ret = phm->obj_index;
		break;
	default:
		break;
	}
	return ret;
}