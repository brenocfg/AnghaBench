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
typedef  size_t u16 ;
struct hpi_response {size_t size; size_t object; size_t function; size_t error; scalar_t__ version; scalar_t__ specific_error; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 size_t HPI_OBJ_MAXINDEX ; 
 int /*<<< orphan*/  HPI_TYPE_RESPONSE ; 
 size_t array_index_nospec (size_t,size_t) ; 
 int /*<<< orphan*/  memset (struct hpi_response*,int /*<<< orphan*/ ,int) ; 
 size_t* res_size ; 

void hpi_init_response(struct hpi_response *phr, u16 object, u16 function,
	u16 error)
{
	u16 size;

	if ((object > 0) && (object <= HPI_OBJ_MAXINDEX)) {
		object = array_index_nospec(object, HPI_OBJ_MAXINDEX + 1);
		size = res_size[object];
	} else {
		size = sizeof(*phr);
	}

	memset(phr, 0, sizeof(*phr));
	phr->size = size;
	phr->type = HPI_TYPE_RESPONSE;
	phr->object = object;
	phr->function = function;
	phr->error = error;
	phr->specific_error = 0;
	phr->version = 0;
}