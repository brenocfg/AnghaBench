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

/* Variables and functions */
 int /*<<< orphan*/  OP_FPERM ; 
 int common_file_perm (int /*<<< orphan*/ ,struct file*,int) ; 

__attribute__((used)) static int apparmor_file_permission(struct file *file, int mask)
{
	return common_file_perm(OP_FPERM, file, mask);
}