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
union pipe {int /*<<< orphan*/  read_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 char PARENT_TOKEN ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 

int wait_for_parent(union pipe read_pipe)
{
	char c;

	FAIL_IF(read(read_pipe.read_fd, &c, 1) != 1);
	FAIL_IF(c != PARENT_TOKEN);

	return 0;
}