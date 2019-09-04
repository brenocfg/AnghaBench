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
typedef  union pipe {int dummy; } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_parent (union pipe) ; 
 int /*<<< orphan*/  wait_for_parent (union pipe) ; 
 int /*<<< orphan*/  write_pmc1 () ; 

__attribute__((used)) static int victim_child(union pipe read_pipe, union pipe write_pipe)
{
	int i;

	FAIL_IF(wait_for_parent(read_pipe));
	FAIL_IF(notify_parent(write_pipe));

	/* Parent creates EBB event */

	FAIL_IF(wait_for_parent(read_pipe));
	FAIL_IF(notify_parent(write_pipe));

	/* Check the EBB is enabled by writing PMC1 */
	write_pmc1();

	/* EBB event is enabled here */
	for (i = 0; i < 1000000; i++) ;

	return 0;
}