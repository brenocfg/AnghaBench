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
struct hpi_message {size_t size; size_t object; size_t function; int /*<<< orphan*/  adapter_index; scalar_t__ version; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ADAPTER_INDEX_INVALID ; 
 size_t HPI_OBJ_MAXINDEX ; 
 int /*<<< orphan*/  HPI_TYPE_REQUEST ; 
 int /*<<< orphan*/  HPI_TYPE_SSX2BYPASS_MESSAGE ; 
 size_t array_index_nospec (size_t,size_t) ; 
 scalar_t__ gwSSX2_bypass ; 
 int /*<<< orphan*/  memset (struct hpi_message*,int /*<<< orphan*/ ,size_t) ; 
 size_t* msg_size ; 

__attribute__((used)) static void hpi_init_message(struct hpi_message *phm, u16 object,
	u16 function)
{
	u16 size;

	if ((object > 0) && (object <= HPI_OBJ_MAXINDEX)) {
		object = array_index_nospec(object, HPI_OBJ_MAXINDEX + 1);
		size = msg_size[object];
	} else {
		size = sizeof(*phm);
	}

	memset(phm, 0, size);
	phm->size = size;

	if (gwSSX2_bypass)
		phm->type = HPI_TYPE_SSX2BYPASS_MESSAGE;
	else
		phm->type = HPI_TYPE_REQUEST;
	phm->object = object;
	phm->function = function;
	phm->version = 0;
	phm->adapter_index = HPI_ADAPTER_INDEX_INVALID;
	/* Expect actual adapter index to be set by caller */
}