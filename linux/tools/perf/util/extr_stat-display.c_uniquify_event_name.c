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
struct evsel {int uniquified_name; char* pmu_name; char* name; } ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uniquify_event_name(struct evsel *counter)
{
	char *new_name;
	char *config;

	if (counter->uniquified_name ||
	    !counter->pmu_name || !strncmp(counter->name, counter->pmu_name,
					   strlen(counter->pmu_name)))
		return;

	config = strchr(counter->name, '/');
	if (config) {
		if (asprintf(&new_name,
			     "%s%s", counter->pmu_name, config) > 0) {
			free(counter->name);
			counter->name = new_name;
		}
	} else {
		if (asprintf(&new_name,
			     "%s [%s]", counter->name, counter->pmu_name) > 0) {
			free(counter->name);
			counter->name = new_name;
		}
	}

	counter->uniquified_name = true;
}