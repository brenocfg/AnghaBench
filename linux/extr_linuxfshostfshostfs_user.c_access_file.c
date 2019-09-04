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
 int R_OK ; 
 int W_OK ; 
 int X_OK ; 
 scalar_t__ access (char*,int) ; 
 int errno ; 

int access_file(char *path, int r, int w, int x)
{
	int mode = 0;

	if (r)
		mode = R_OK;
	if (w)
		mode |= W_OK;
	if (x)
		mode |= X_OK;
	if (access(path, mode) != 0)
		return -errno;
	else return 0;
}