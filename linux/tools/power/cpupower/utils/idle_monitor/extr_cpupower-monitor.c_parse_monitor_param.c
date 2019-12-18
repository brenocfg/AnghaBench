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
struct cpuidle_monitor {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int MONITORS_MAX ; 
 scalar_t__ MONITOR_NAME_LEN ; 
 char* _ (char*) ; 
 unsigned int avail_monitors ; 
 int /*<<< orphan*/  dprint (char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct cpuidle_monitor**,struct cpuidle_monitor**,int) ; 
 struct cpuidle_monitor** monitors ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static void parse_monitor_param(char *param)
{
	unsigned int num;
	int mon, hits = 0;
	char *tmp = param, *token;
	struct cpuidle_monitor *tmp_mons[MONITORS_MAX];


	for (mon = 0; mon < MONITORS_MAX; mon++, tmp = NULL) {
		token = strtok(tmp, ",");
		if (token == NULL)
			break;
		if (strlen(token) >= MONITOR_NAME_LEN) {
			printf(_("%s: max monitor name length"
				 " (%d) exceeded\n"), token, MONITOR_NAME_LEN);
			continue;
		}

		for (num = 0; num < avail_monitors; num++) {
			if (!strcmp(monitors[num]->name, token)) {
				dprint("Found requested monitor: %s\n", token);
				tmp_mons[hits] = monitors[num];
				hits++;
			}
		}
	}
	if (hits == 0) {
		printf(_("No matching monitor found in %s, "
			 "try -l option\n"), param);
		exit(EXIT_FAILURE);
	}
	/* Override detected/registerd monitors array with requested one */
	memcpy(monitors, tmp_mons,
		sizeof(struct cpuidle_monitor *) * MONITORS_MAX);
	avail_monitors = hits;
}