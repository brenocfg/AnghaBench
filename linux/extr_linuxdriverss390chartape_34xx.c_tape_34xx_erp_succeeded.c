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

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*,int /*<<< orphan*/ ) ; 
 int tape_34xx_done (struct tape_request*) ; 
 int /*<<< orphan*/ * tape_op_verbose ; 

__attribute__((used)) static inline int
tape_34xx_erp_succeeded(struct tape_request *request)
{
	DBF_EVENT(3, "Error Recovery successful for %s\n",
		  tape_op_verbose[request->op]);
	return tape_34xx_done(request);
}