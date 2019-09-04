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
typedef  size_t ssize_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf1 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t readlink (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int streq (char*,char*) ; 
 size_t strlen (char*) ; 
 int sys_getpid () ; 

int main(void)
{
	char buf1[64], buf2[64];
	pid_t pid;
	ssize_t rv;

	pid = sys_getpid();
	snprintf(buf1, sizeof(buf1), "%u", pid);

	rv = readlink("/proc/self", buf2, sizeof(buf2));
	assert(rv == strlen(buf1));
	buf2[rv] = '\0';
	assert(streq(buf1, buf2));

	return 0;
}