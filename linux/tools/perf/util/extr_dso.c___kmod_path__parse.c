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
struct kmod_path {int kmod; int /*<<< orphan*/  name; int /*<<< orphan*/  comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ID__NONE ; 
 int ENOMEM ; 
 int asprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  is_supported_compression (char const*) ; 
 int /*<<< orphan*/  memset (struct kmod_path*,int,int) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  strreplace (int /*<<< orphan*/ ,char,char) ; 

int __kmod_path__parse(struct kmod_path *m, const char *path,
		       bool alloc_name)
{
	const char *name = strrchr(path, '/');
	const char *ext  = strrchr(path, '.');
	bool is_simple_name = false;

	memset(m, 0x0, sizeof(*m));
	name = name ? name + 1 : path;

	/*
	 * '.' is also a valid character for module name. For example:
	 * [aaa.bbb] is a valid module name. '[' should have higher
	 * priority than '.ko' suffix.
	 *
	 * The kernel names are from machine__mmap_name. Such
	 * name should belong to kernel itself, not kernel module.
	 */
	if (name[0] == '[') {
		is_simple_name = true;
		if ((strncmp(name, "[kernel.kallsyms]", 17) == 0) ||
		    (strncmp(name, "[guest.kernel.kallsyms", 22) == 0) ||
		    (strncmp(name, "[vdso]", 6) == 0) ||
		    (strncmp(name, "[vdso32]", 8) == 0) ||
		    (strncmp(name, "[vdsox32]", 9) == 0) ||
		    (strncmp(name, "[vsyscall]", 10) == 0)) {
			m->kmod = false;

		} else
			m->kmod = true;
	}

	/* No extension, just return name. */
	if ((ext == NULL) || is_simple_name) {
		if (alloc_name) {
			m->name = strdup(name);
			return m->name ? 0 : -ENOMEM;
		}
		return 0;
	}

	m->comp = is_supported_compression(ext + 1);
	if (m->comp > COMP_ID__NONE)
		ext -= 3;

	/* Check .ko extension only if there's enough name left. */
	if (ext > name)
		m->kmod = !strncmp(ext, ".ko", 3);

	if (alloc_name) {
		if (m->kmod) {
			if (asprintf(&m->name, "[%.*s]", (int) (ext - name), name) == -1)
				return -ENOMEM;
		} else {
			if (asprintf(&m->name, "%s", name) == -1)
				return -ENOMEM;
		}

		strreplace(m->name, '-', '_');
	}

	return 0;
}