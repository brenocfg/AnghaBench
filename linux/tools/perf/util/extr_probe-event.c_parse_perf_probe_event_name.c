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
struct perf_probe_event {char* group; char* event; int /*<<< orphan*/  sdt; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  is_c_func_name (char*) ; 
 int /*<<< orphan*/  semantic_error (char*,char*) ; 
 void* strdup_esc (char*) ; 
 char* strpbrk_esc (char*,char*) ; 
 int /*<<< orphan*/  zfree (char**) ; 

__attribute__((used)) static int parse_perf_probe_event_name(char **arg, struct perf_probe_event *pev)
{
	char *ptr;

	ptr = strpbrk_esc(*arg, ":");
	if (ptr) {
		*ptr = '\0';
		if (!pev->sdt && !is_c_func_name(*arg))
			goto ng_name;
		pev->group = strdup_esc(*arg);
		if (!pev->group)
			return -ENOMEM;
		*arg = ptr + 1;
	} else
		pev->group = NULL;

	pev->event = strdup_esc(*arg);
	if (pev->event == NULL)
		return -ENOMEM;

	if (!pev->sdt && !is_c_func_name(pev->event)) {
		zfree(&pev->event);
ng_name:
		zfree(&pev->group);
		semantic_error("%s is bad for event name -it must "
			       "follow C symbol-naming rule.\n", *arg);
		return -EINVAL;
	}
	return 0;
}