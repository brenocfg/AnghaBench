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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int event_trigger_regex_open (struct inode*,struct file*) ; 

__attribute__((used)) static int
event_trigger_open(struct inode *inode, struct file *filp)
{
	/* Checks for tracefs lockdown */
	return event_trigger_regex_open(inode, filp);
}