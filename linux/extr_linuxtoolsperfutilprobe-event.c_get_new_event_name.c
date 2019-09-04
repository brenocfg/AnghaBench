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
struct strlist {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ERANGE ; 
 int MAX_EVENT_INDEX ; 
 int e_snprintf (char*,size_t,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  is_c_func_name (char*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strlist__has_entry (struct strlist*,char*) ; 
 char* strpbrk (char*,char*) ; 

__attribute__((used)) static int get_new_event_name(char *buf, size_t len, const char *base,
			      struct strlist *namelist, bool ret_event,
			      bool allow_suffix)
{
	int i, ret;
	char *p, *nbase;

	if (*base == '.')
		base++;
	nbase = strdup(base);
	if (!nbase)
		return -ENOMEM;

	/* Cut off the dot suffixes (e.g. .const, .isra) and version suffixes */
	p = strpbrk(nbase, ".@");
	if (p && p != nbase)
		*p = '\0';

	/* Try no suffix number */
	ret = e_snprintf(buf, len, "%s%s", nbase, ret_event ? "__return" : "");
	if (ret < 0) {
		pr_debug("snprintf() failed: %d\n", ret);
		goto out;
	}
	if (!strlist__has_entry(namelist, buf))
		goto out;

	if (!allow_suffix) {
		pr_warning("Error: event \"%s\" already exists.\n"
			   " Hint: Remove existing event by 'perf probe -d'\n"
			   "       or force duplicates by 'perf probe -f'\n"
			   "       or set 'force=yes' in BPF source.\n",
			   buf);
		ret = -EEXIST;
		goto out;
	}

	/* Try to add suffix */
	for (i = 1; i < MAX_EVENT_INDEX; i++) {
		ret = e_snprintf(buf, len, "%s_%d", nbase, i);
		if (ret < 0) {
			pr_debug("snprintf() failed: %d\n", ret);
			goto out;
		}
		if (!strlist__has_entry(namelist, buf))
			break;
	}
	if (i == MAX_EVENT_INDEX) {
		pr_warning("Too many events are on the same function.\n");
		ret = -ERANGE;
	}

out:
	free(nbase);

	/* Final validation */
	if (ret >= 0 && !is_c_func_name(buf)) {
		pr_warning("Internal error: \"%s\" is an invalid event name.\n",
			   buf);
		ret = -EINVAL;
	}

	return ret;
}