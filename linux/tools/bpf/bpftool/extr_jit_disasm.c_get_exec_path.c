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
 int /*<<< orphan*/  assert (int) ; 
 size_t readlink (char const*,char*,size_t) ; 

__attribute__((used)) static void get_exec_path(char *tpath, size_t size)
{
	const char *path = "/proc/self/exe";
	ssize_t len;

	len = readlink(path, tpath, size - 1);
	assert(len > 0);
	tpath[len] = 0;
}