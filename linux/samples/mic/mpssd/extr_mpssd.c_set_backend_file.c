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
struct TYPE_2__ {int /*<<< orphan*/ * backend_file; } ;
struct mic_info {int id; TYPE_1__ mic_virtblk; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 char* mic_config_dir ; 
 int /*<<< orphan*/  mpsslog (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,scalar_t__) ; 
 char* virtblk_backend ; 

__attribute__((used)) static bool
set_backend_file(struct mic_info *mic)
{
	FILE *config;
	char buff[PATH_MAX], *line, *evv, *p;

	snprintf(buff, PATH_MAX, "%s/mpssd%03d.conf", mic_config_dir, mic->id);
	config = fopen(buff, "r");
	if (config == NULL)
		return false;
	do {  /* look for "virtblk_backend=XXXX" */
		line = fgets(buff, PATH_MAX, config);
		if (line == NULL)
			break;
		if (*line == '#')
			continue;
		p = strchr(line, '\n');
		if (p)
			*p = '\0';
	} while (strncmp(line, virtblk_backend, strlen(virtblk_backend)) != 0);
	fclose(config);
	if (line == NULL)
		return false;
	evv = strchr(line, '=');
	if (evv == NULL)
		return false;
	mic->mic_virtblk.backend_file = malloc(strlen(evv) + 1);
	if (mic->mic_virtblk.backend_file == NULL) {
		mpsslog("%s %d can't allocate memory\n", mic->name, mic->id);
		return false;
	}
	strcpy(mic->mic_virtblk.backend_file, evv + 1);
	return true;
}