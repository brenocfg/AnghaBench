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
typedef  int /*<<< orphan*/  u16 ;
struct hpi_response_header {int version; int /*<<< orphan*/  error; int /*<<< orphan*/  type; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ERROR_PROCESSING_MESSAGE ; 
 int /*<<< orphan*/  HPI_TYPE_RESPONSE ; 
 int /*<<< orphan*/  memset (struct hpi_response_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hpi_init_responseV1(struct hpi_response_header *phr, u16 size,
	u16 object, u16 function)
{
	(void)object;
	(void)function;
	memset(phr, 0, size);
	phr->size = size;
	phr->version = 1;
	phr->type = HPI_TYPE_RESPONSE;
	phr->error = HPI_ERROR_PROCESSING_MESSAGE;
}