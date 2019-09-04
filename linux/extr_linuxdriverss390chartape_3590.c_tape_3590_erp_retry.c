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
struct tape_request {size_t op; } ;
struct tape_device {int dummy; } ;
struct irb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*,int /*<<< orphan*/ ) ; 
 int TAPE_IO_RETRY ; 
 int /*<<< orphan*/  tape_dump_sense_dbf (struct tape_device*,struct tape_request*,struct irb*) ; 
 int /*<<< orphan*/ * tape_op_verbose ; 

__attribute__((used)) static inline int
tape_3590_erp_retry(struct tape_device *device, struct tape_request *request,
		    struct irb *irb)
{
	DBF_EVENT(2, "Retry: %s\n", tape_op_verbose[request->op]);
	tape_dump_sense_dbf(device, request, irb);
	return TAPE_IO_RETRY;
}