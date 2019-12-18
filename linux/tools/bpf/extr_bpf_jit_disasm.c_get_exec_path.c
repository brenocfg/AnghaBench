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

/* Variables and functions */
 int /*<<< orphan*/  assert (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getpid () ; 
 size_t readlink (char*,char*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 
 char* strdup (char*) ; 

__attribute__((used)) static void get_exec_path(char *tpath, size_t size)
{
	char *path;
	ssize_t len;

	snprintf(tpath, size, "/proc/%d/exe", (int) getpid());
	tpath[size - 1] = 0;

	path = strdup(tpath);
	assert(path);

	len = readlink(path, tpath, size);
	tpath[len] = 0;

	free(path);
}