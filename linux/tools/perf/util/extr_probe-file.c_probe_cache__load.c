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
struct probe_cache_entry {int sdt; int /*<<< orphan*/  tevlist; int /*<<< orphan*/  node; int /*<<< orphan*/  pev; scalar_t__ spev; } ;
struct probe_cache {int /*<<< orphan*/  entries; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int MAX_CMDLEN ; 
 int /*<<< orphan*/  close (int) ; 
 int dup (int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int parse_perf_probe_command (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  probe_cache_entry__delete (struct probe_cache_entry*) ; 
 struct probe_cache_entry* probe_cache_entry__new (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strdup (char*) ; 
 int /*<<< orphan*/  strlist__add (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int probe_cache__load(struct probe_cache *pcache)
{
	struct probe_cache_entry *entry = NULL;
	char buf[MAX_CMDLEN], *p;
	int ret = 0, fddup;
	FILE *fp;

	fddup = dup(pcache->fd);
	if (fddup < 0)
		return -errno;
	fp = fdopen(fddup, "r");
	if (!fp) {
		close(fddup);
		return -EINVAL;
	}

	while (!feof(fp)) {
		if (!fgets(buf, MAX_CMDLEN, fp))
			break;
		p = strchr(buf, '\n');
		if (p)
			*p = '\0';
		/* #perf_probe_event or %sdt_event */
		if (buf[0] == '#' || buf[0] == '%') {
			entry = probe_cache_entry__new(NULL);
			if (!entry) {
				ret = -ENOMEM;
				goto out;
			}
			if (buf[0] == '%')
				entry->sdt = true;
			entry->spev = strdup(buf + 1);
			if (entry->spev)
				ret = parse_perf_probe_command(buf + 1,
								&entry->pev);
			else
				ret = -ENOMEM;
			if (ret < 0) {
				probe_cache_entry__delete(entry);
				goto out;
			}
			list_add_tail(&entry->node, &pcache->entries);
		} else {	/* trace_probe_event */
			if (!entry) {
				ret = -EINVAL;
				goto out;
			}
			strlist__add(entry->tevlist, buf);
		}
	}
out:
	fclose(fp);
	return ret;
}