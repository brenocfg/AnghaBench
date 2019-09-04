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
struct hpi_message {scalar_t__ adapter_index; scalar_t__ object; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ERROR_INVALID_OBJ_INDEX ; 
 scalar_t__ HPI_MAX_ADAPTERS ; 
 scalar_t__ HPI_OBJ_SUBSYSTEM ; 
 int /*<<< orphan*/  hpi_send_recv_ex (struct hpi_message*,struct hpi_response*,struct file*) ; 

__attribute__((used)) static void hpi_send_recv_f(struct hpi_message *phm, struct hpi_response *phr,
	struct file *file)
{
	if ((phm->adapter_index >= HPI_MAX_ADAPTERS)
		&& (phm->object != HPI_OBJ_SUBSYSTEM))
		phr->error = HPI_ERROR_INVALID_OBJ_INDEX;
	else
		hpi_send_recv_ex(phm, phr, file);
}