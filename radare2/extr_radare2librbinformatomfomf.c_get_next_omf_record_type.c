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
typedef  scalar_t__ ut8 ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ OMF_record_handler ;
typedef  TYPE_2__ OMF_record ;

/* Variables and functions */

__attribute__((used)) static OMF_record_handler *get_next_omf_record_type(OMF_record_handler *tmp, ut8 type) {
	while (tmp) {
		if (((OMF_record *)tmp)->type == type) {
			return (tmp);
		}
		tmp = tmp->next;
	}
	return NULL;
}