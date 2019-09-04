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
struct mic_info {int /*<<< orphan*/  id; scalar_t__ name; struct mic_info* next; } ;
struct dirent {int /*<<< orphan*/ * d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  MICSYSFSDIR ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ *) ; 
 struct mic_info* calloc (int,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (scalar_t__) ; 
 struct mic_info mic_list ; 
 int /*<<< orphan*/  mpsslog (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
init_mic_list(void)
{
	struct mic_info *mic = &mic_list;
	struct dirent *file;
	DIR *dp;
	int cnt = 0;

	dp = opendir(MICSYSFSDIR);
	if (!dp)
		return 0;

	while ((file = readdir(dp)) != NULL) {
		if (!strncmp(file->d_name, "mic", 3)) {
			mic->next = calloc(1, sizeof(struct mic_info));
			if (mic->next) {
				mic = mic->next;
				mic->id = atoi(&file->d_name[3]);
				mic->name = malloc(strlen(file->d_name) + 16);
				if (mic->name)
					strcpy(mic->name, file->d_name);
				mpsslog("MIC name %s id %d\n", mic->name,
					mic->id);
				cnt++;
			}
		}
	}

	closedir(dp);
	return cnt;
}