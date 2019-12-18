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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int filename__read_str (char*,char**,size_t*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  procfs__mountpoint () ; 
 int /*<<< orphan*/  strim (char*) ; 

__attribute__((used)) static int get_comm(char **comm, pid_t pid)
{
	char *path;
	size_t size;
	int err;

	if (asprintf(&path, "%s/%d/comm", procfs__mountpoint(), pid) == -1)
		return -ENOMEM;

	err = filename__read_str(path, comm, &size);
	if (!err) {
		/*
		 * We're reading 16 bytes, while filename__read_str
		 * allocates data per BUFSIZ bytes, so we can safely
		 * mark the end of the string.
		 */
		(*comm)[size] = 0;
		strim(*comm);
	}

	free(path);
	return err;
}