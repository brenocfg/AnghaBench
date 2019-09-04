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
typedef  scalar_t__ u16 ;
struct hpi_message_header {int version; scalar_t__ function; scalar_t__ object; int /*<<< orphan*/  type; scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ HPI_OBJ_MAXINDEX ; 
 int /*<<< orphan*/  HPI_TYPE_REQUEST ; 
 int /*<<< orphan*/  memset (struct hpi_message_header*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hpi_init_messageV1(struct hpi_message_header *phm, u16 size,
	u16 object, u16 function)
{
	memset(phm, 0, size);
	if ((object > 0) && (object <= HPI_OBJ_MAXINDEX)) {
		phm->size = size;
		phm->type = HPI_TYPE_REQUEST;
		phm->object = object;
		phm->function = function;
		phm->version = 1;
		/* Expect adapter index to be set by caller */
	}
}