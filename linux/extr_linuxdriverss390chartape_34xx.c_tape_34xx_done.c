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
struct tape_request {size_t op; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*,int /*<<< orphan*/ ) ; 
 int TAPE_IO_SUCCESS ; 
#define  TO_ASSIGN 133 
#define  TO_DSE 132 
#define  TO_RUN 131 
#define  TO_UNASSIGN 130 
#define  TO_WRI 129 
#define  TO_WTM 128 
 int /*<<< orphan*/  tape_34xx_delete_sbid_from (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tape_op_verbose ; 

__attribute__((used)) static inline int
tape_34xx_done(struct tape_request *request)
{
	DBF_EVENT(6, "%s done\n", tape_op_verbose[request->op]);

	switch (request->op) {
		case TO_DSE:
		case TO_RUN:
		case TO_WRI:
		case TO_WTM:
		case TO_ASSIGN:
		case TO_UNASSIGN:
			tape_34xx_delete_sbid_from(request->device, 0);
			break;
		default:
			;
	}
	return TAPE_IO_SUCCESS;
}