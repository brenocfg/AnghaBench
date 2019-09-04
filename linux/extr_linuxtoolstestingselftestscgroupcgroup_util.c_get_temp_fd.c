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
 int O_EXCL ; 
 int O_RDWR ; 
 int O_TMPFILE ; 
 int open (char*,int) ; 

int get_temp_fd(void)
{
	return open(".", O_TMPFILE | O_RDWR | O_EXCL);
}