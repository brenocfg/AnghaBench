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
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int PATH_MAX ; 
 char read_text (char*,char*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char const*) ; 

char proc_read_text(int pid, const char *item, char *buf, size_t size)
{
	char path[PATH_MAX];

	snprintf(path, sizeof(path), "/proc/%d/%s", pid, item);

	return read_text(path, buf, size);
}