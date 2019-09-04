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
struct file {struct file* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct file* file_list ; 
 int /*<<< orphan*/  memset (struct file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 struct file* xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

struct file *file_lookup(const char *name)
{
	struct file *file;

	for (file = file_list; file; file = file->next) {
		if (!strcmp(name, file->name)) {
			return file;
		}
	}

	file = xmalloc(sizeof(*file));
	memset(file, 0, sizeof(*file));
	file->name = xstrdup(name);
	file->next = file_list;
	file_list = file;
	return file;
}