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
union pipe {int /*<<< orphan*/  write_fd; } ;

/* Variables and functions */
 char CHILD_TOKEN ; 
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

int notify_parent(union pipe write_pipe)
{
	char c = CHILD_TOKEN;

	FAIL_IF(write(write_pipe.write_fd, &c, 1) != 1);

	return 0;
}