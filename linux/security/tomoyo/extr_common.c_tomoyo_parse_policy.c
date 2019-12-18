#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int is_delete; int /*<<< orphan*/ * ns; } ;
struct tomoyo_io_buffer {scalar_t__ type; int (* write ) (struct tomoyo_io_buffer*) ;TYPE_1__ w; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ TOMOYO_EXCEPTIONPOLICY ; 
 scalar_t__ TOMOYO_PROFILE ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int stub1 (struct tomoyo_io_buffer*) ; 
 int /*<<< orphan*/ * tomoyo_assign_namespace (char*) ; 
 int /*<<< orphan*/  tomoyo_kernel_namespace ; 

__attribute__((used)) static int tomoyo_parse_policy(struct tomoyo_io_buffer *head, char *line)
{
	/* Delete request? */
	head->w.is_delete = !strncmp(line, "delete ", 7);
	if (head->w.is_delete)
		memmove(line, line + 7, strlen(line + 7) + 1);
	/* Selecting namespace to update. */
	if (head->type == TOMOYO_EXCEPTIONPOLICY ||
	    head->type == TOMOYO_PROFILE) {
		if (*line == '<') {
			char *cp = strchr(line, ' ');

			if (cp) {
				*cp++ = '\0';
				head->w.ns = tomoyo_assign_namespace(line);
				memmove(line, cp, strlen(cp) + 1);
			} else
				head->w.ns = NULL;
		} else
			head->w.ns = &tomoyo_kernel_namespace;
		/* Don't allow updating if namespace is invalid. */
		if (!head->w.ns)
			return -ENOENT;
	}
	/* Do the update. */
	return head->write(head);
}