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
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_INHERIT ; 
 scalar_t__ aa_file_perm (int /*<<< orphan*/ ,struct aa_label*,struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_map_file_to_perms (struct file*) ; 

__attribute__((used)) static int match_file(const void *p, struct file *file, unsigned int fd)
{
	struct aa_label *label = (struct aa_label *)p;

	if (aa_file_perm(OP_INHERIT, label, file, aa_map_file_to_perms(file)))
		return fd + 1;
	return 0;
}