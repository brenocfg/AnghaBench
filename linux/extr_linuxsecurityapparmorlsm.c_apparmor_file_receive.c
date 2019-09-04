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
 int /*<<< orphan*/  OP_FRECEIVE ; 
 int /*<<< orphan*/  aa_map_file_to_perms (struct file*) ; 
 int common_file_perm (int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apparmor_file_receive(struct file *file)
{
	return common_file_perm(OP_FRECEIVE, file, aa_map_file_to_perms(file));
}