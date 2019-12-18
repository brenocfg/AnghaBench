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
struct hpi_response {int dummy; } ;
struct hpi_message {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_OBJ_SUBSYSTEM ; 
 int /*<<< orphan*/  HPI_SUBSYS_CLOSE ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv_ex (struct hpi_message*,struct hpi_response*,struct file*) ; 

int asihpi_hpi_release(struct file *file)
{
	struct hpi_message hm;
	struct hpi_response hr;

/* HPI_DEBUG_LOG(INFO,"hpi_release file %p, pid %d\n", file, current->pid); */
	/* close the subsystem just in case the application forgot to. */
	hpi_init_message_response(&hm, &hr, HPI_OBJ_SUBSYSTEM,
		HPI_SUBSYS_CLOSE);
	hpi_send_recv_ex(&hm, &hr, file);
	return 0;
}