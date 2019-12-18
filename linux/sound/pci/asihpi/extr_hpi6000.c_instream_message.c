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
struct hpi_response {int /*<<< orphan*/  error; } ;
struct hpi_message {int function; } ;
struct hpi_adapter_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ERROR_INVALID_FUNC ; 
#define  HPI_ISTREAM_HOSTBUFFER_ALLOC 129 
#define  HPI_ISTREAM_HOSTBUFFER_FREE 128 
 int /*<<< orphan*/  hw_message (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 

__attribute__((used)) static void instream_message(struct hpi_adapter_obj *pao,
	struct hpi_message *phm, struct hpi_response *phr)
{

	switch (phm->function) {
	case HPI_ISTREAM_HOSTBUFFER_ALLOC:
	case HPI_ISTREAM_HOSTBUFFER_FREE:
		/* Don't let these messages go to the HW function because
		 * they're called without locking the spinlock.
		 * For the HPI6000 adapters the HW would return
		 * HPI_ERROR_INVALID_FUNC anyway.
		 */
		phr->error = HPI_ERROR_INVALID_FUNC;
		break;
	default:
		hw_message(pao, phm, phr);
		return;
	}
}