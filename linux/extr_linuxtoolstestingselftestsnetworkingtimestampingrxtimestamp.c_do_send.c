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

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_size ; 
 int write (int,char*,int /*<<< orphan*/ ) ; 

void do_send(int src)
{
	int r;
	char *buf = malloc(op_size);

	memset(buf, 'z', op_size);
	r = write(src, buf, op_size);
	if (r < 0)
		error(1, errno, "Failed to sendmsg");

	free(buf);
}