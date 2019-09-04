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
union pipe {int /*<<< orphan*/  read_fd; int /*<<< orphan*/  write_fd; } ;

/* Variables and functions */
 char CHILD_TOKEN ; 
 int /*<<< orphan*/  FAIL_IF (int) ; 
 char PARENT_TOKEN ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

int sync_with_child(union pipe read_pipe, union pipe write_pipe)
{
	char c = PARENT_TOKEN;

	FAIL_IF(write(write_pipe.write_fd, &c, 1) != 1);
	FAIL_IF(read(read_pipe.read_fd, &c, 1) != 1);
	if (c != CHILD_TOKEN) /* sometimes expected */
		return 1;

	return 0;
}