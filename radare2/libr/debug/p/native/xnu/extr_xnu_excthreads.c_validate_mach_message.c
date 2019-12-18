#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  mach_msg_port_descriptor_t ;
typedef  int /*<<< orphan*/  mach_msg_header_t ;
typedef  int /*<<< orphan*/  mach_msg_body_t ;
typedef  int /*<<< orphan*/  mach_exception_data_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  exception_type_t ;
struct TYPE_15__ {scalar_t__ name; } ;
struct TYPE_14__ {scalar_t__ name; } ;
struct TYPE_13__ {scalar_t__ mig_vers; scalar_t__ if_vers; scalar_t__ mig_encoding; scalar_t__ int_rep; scalar_t__ char_rep; scalar_t__ float_rep; } ;
struct TYPE_12__ {scalar_t__ msgh_local_port; int msgh_bits; int msgh_id; int msgh_size; } ;
struct TYPE_16__ {TYPE_4__ thread; TYPE_3__ task; TYPE_2__ NDR; TYPE_1__ hdr; } ;
typedef  TYPE_5__ exc_msg ;
struct TYPE_18__ {scalar_t__ exception_port; } ;
struct TYPE_17__ {int /*<<< orphan*/  pid; } ;
struct TYPE_11__ {scalar_t__ mig_encoding; scalar_t__ int_rep; scalar_t__ char_rep; scalar_t__ float_rep; } ;
typedef  TYPE_6__ RDebug ;
typedef  int /*<<< orphan*/  NDR_record_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int MACH_MSGH_BITS_COMPLEX ; 
 scalar_t__ NDR_PROTOCOL_2_0 ; 
 TYPE_10__ NDR_record ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 TYPE_9__ ex ; 
 scalar_t__ mach_port_deallocate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 scalar_t__ pid_to_task (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool validate_mach_message (RDebug *dbg, exc_msg *msg) {
	kern_return_t kr;
#if __POWERPC__
	return false;
#else
	/*check if the message is for us*/
	if (msg->hdr.msgh_local_port != ex.exception_port) {
		return false;
	}
	/*gdb from apple check this so why not us*/
	if (!(msg->hdr.msgh_bits & MACH_MSGH_BITS_COMPLEX)) {
		return false;
	}
	/*mach exception we are interested*/
	//XXX for i386 this id seems to be different
	if (msg->hdr.msgh_id > 2405 || msg->hdr.msgh_id < 2401) {
		return false;
	}
	/* check descriptors.  */
	if (msg->hdr.msgh_size <
	    sizeof (mach_msg_header_t) + sizeof (mach_msg_body_t) +
		    2 * sizeof (mach_msg_port_descriptor_t) +
		    sizeof (NDR_record_t) + sizeof (exception_type_t) +
		    sizeof (mach_msg_type_number_t) +
		    sizeof (mach_exception_data_t))
		return false;
	/* check data representation.  */
	if (msg->NDR.mig_vers != NDR_PROTOCOL_2_0 ||
	    msg->NDR.if_vers != NDR_PROTOCOL_2_0 ||
	    msg->NDR.mig_encoding != NDR_record.mig_encoding ||
	    msg->NDR.int_rep != NDR_record.int_rep ||
	    msg->NDR.char_rep != NDR_record.char_rep ||
	    msg->NDR.float_rep != NDR_record.float_rep) {
		return false;
	}
	if (pid_to_task (dbg->pid) != msg->task.name) {
		//we receive a exception from an unknown process this could
		//happen if the child fork, as the created process will inherit
		//its exception port
		/*we got new rights to the task, get rid of it.*/
		kr = mach_port_deallocate (mach_task_self (), msg->task.name);
		if (kr != KERN_SUCCESS) {
			eprintf ("validate_mach_message: failed to deallocate task port\n");
		}
		kr = mach_port_deallocate (mach_task_self (), msg->thread.name);
		if (kr != KERN_SUCCESS) {
			eprintf ("validate_mach_message2: failed to deallocated task port\n");
		}
		return false;
	}
	return true;
#endif
}