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
struct file {int dummy; } ;
struct fasync_struct {int dummy; } ;

/* Variables and functions */
 int fasync_add_entry (int,struct file*,struct fasync_struct**) ; 
 int fasync_remove_entry (struct file*,struct fasync_struct**) ; 

int fasync_helper(int fd, struct file * filp, int on, struct fasync_struct **fapp)
{
	if (!on)
		return fasync_remove_entry(filp, fapp);
	return fasync_add_entry(fd, filp, fapp);
}