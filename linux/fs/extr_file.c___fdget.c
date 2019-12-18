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
 int /*<<< orphan*/  FMODE_PATH ; 
 unsigned long __fget_light (unsigned int,int /*<<< orphan*/ ) ; 

unsigned long __fdget(unsigned int fd)
{
	return __fget_light(fd, FMODE_PATH);
}