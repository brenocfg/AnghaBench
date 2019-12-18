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
struct file_security_struct {int /*<<< orphan*/  fown_sid; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_sid () ; 
 struct file_security_struct* selinux_file (struct file*) ; 

__attribute__((used)) static void selinux_file_set_fowner(struct file *file)
{
	struct file_security_struct *fsec;

	fsec = selinux_file(file);
	fsec->fown_sid = current_sid();
}