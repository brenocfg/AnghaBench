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
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PAGE_SIZE ; 
 int get_cmdline (struct task_struct*,char*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 char* kstrdup_quotable (char*,int /*<<< orphan*/ ) ; 

char *kstrdup_quotable_cmdline(struct task_struct *task, gfp_t gfp)
{
	char *buffer, *quoted;
	int i, res;

	buffer = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (!buffer)
		return NULL;

	res = get_cmdline(task, buffer, PAGE_SIZE - 1);
	buffer[res] = '\0';

	/* Collapse trailing NULLs, leave res pointing to last non-NULL. */
	while (--res >= 0 && buffer[res] == '\0')
		;

	/* Replace inter-argument NULLs. */
	for (i = 0; i <= res; i++)
		if (buffer[i] == '\0')
			buffer[i] = ' ';

	/* Make sure result is printable. */
	quoted = kstrdup_quotable(buffer, gfp);
	kfree(buffer);
	return quoted;
}