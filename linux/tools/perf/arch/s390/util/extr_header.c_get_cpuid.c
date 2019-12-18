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
typedef  int /*<<< orphan*/  version ;
typedef  int /*<<< orphan*/  type ;
typedef  int /*<<< orphan*/  model ;
typedef  int /*<<< orphan*/  manufacturer ;
typedef  int /*<<< orphan*/  authorization ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  SRVLVL ; 
 int /*<<< orphan*/  SRVLVL_AUTHORIZATION ; 
 int /*<<< orphan*/  SRVLVL_CPUMF ; 
 int /*<<< orphan*/  SRVLVL_VERSION ; 
 int /*<<< orphan*/  SYSINFO ; 
 int /*<<< orphan*/  SYSINFO_MANU ; 
 int /*<<< orphan*/  SYSINFO_MODEL ; 
 int /*<<< orphan*/  SYSINFO_TYPE ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ scnprintf (char*,int,char*,char*,...) ; 
 size_t snprintf (char*,size_t,char*,char*,char*,char*,...) ; 
 char* strchr (char*,char) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 
 char* strtok_r (char*,char*,char**) ; 

int get_cpuid(char *buffer, size_t sz)
{
	char *cp, *line = NULL, *line2;
	char type[8], model[33], version[8], manufacturer[32], authorization[8];
	int tpsize = 0, mdsize = 0, vssize = 0, mfsize = 0, atsize = 0;
	int read;
	unsigned long line_sz;
	size_t nbytes;
	FILE *sysinfo;

	/*
	 * Scan /proc/sysinfo line by line and read out values for
	 * Manufacturer:, Type: and Model:, for example:
	 * Manufacturer:    IBM
	 * Type:            2964
	 * Model:           702              N96
	 * The first word is the Model Capacity and the second word is
	 * Model (can be omitted). Both words have a maximum size of 16
	 * bytes.
	 */
	memset(manufacturer, 0, sizeof(manufacturer));
	memset(type, 0, sizeof(type));
	memset(model, 0, sizeof(model));
	memset(version, 0, sizeof(version));
	memset(authorization, 0, sizeof(authorization));

	sysinfo = fopen(SYSINFO, "r");
	if (sysinfo == NULL)
		return errno;

	while ((read = getline(&line, &line_sz, sysinfo)) != -1) {
		if (!strncmp(line, SYSINFO_MANU, strlen(SYSINFO_MANU))) {
			line2 = line + strlen(SYSINFO_MANU);

			while ((cp = strtok_r(line2, "\n ", &line2))) {
				mfsize += scnprintf(manufacturer + mfsize,
						    sizeof(manufacturer) - mfsize, "%s", cp);
			}
		}

		if (!strncmp(line, SYSINFO_TYPE, strlen(SYSINFO_TYPE))) {
			line2 = line + strlen(SYSINFO_TYPE);

			while ((cp = strtok_r(line2, "\n ", &line2))) {
				tpsize += scnprintf(type + tpsize,
						    sizeof(type) - tpsize, "%s", cp);
			}
		}

		if (!strncmp(line, SYSINFO_MODEL, strlen(SYSINFO_MODEL))) {
			line2 = line + strlen(SYSINFO_MODEL);

			while ((cp = strtok_r(line2, "\n ", &line2))) {
				mdsize += scnprintf(model + mdsize, sizeof(model) - mdsize,
						    "%s%s", model[0] ? "," : "", cp);
			}
			break;
		}
	}
	fclose(sysinfo);

	/* Missing manufacturer, type or model information should not happen */
	if (!manufacturer[0] || !type[0] || !model[0])
		return EINVAL;

	/*
	 * Scan /proc/service_levels and return the CPU-MF counter facility
	 * version number and authorization level.
	 * Optional, does not exist on z/VM guests.
	 */
	sysinfo = fopen(SRVLVL, "r");
	if (sysinfo == NULL)
		goto skip_sysinfo;
	while ((read = getline(&line, &line_sz, sysinfo)) != -1) {
		if (strncmp(line, SRVLVL_CPUMF, strlen(SRVLVL_CPUMF)))
			continue;

		line2 = line + strlen(SRVLVL_CPUMF);
		while ((cp = strtok_r(line2, "\n ", &line2))) {
			if (!strncmp(cp, SRVLVL_VERSION,
				     strlen(SRVLVL_VERSION))) {
				char *sep = strchr(cp, '=');

				vssize += scnprintf(version + vssize,
						    sizeof(version) - vssize, "%s", sep + 1);
			}
			if (!strncmp(cp, SRVLVL_AUTHORIZATION,
				     strlen(SRVLVL_AUTHORIZATION))) {
				char *sep = strchr(cp, '=');

				atsize += scnprintf(authorization + atsize,
						    sizeof(authorization) - atsize, "%s", sep + 1);
			}
		}
	}
	fclose(sysinfo);

skip_sysinfo:
	free(line);

	if (version[0] && authorization[0] )
		nbytes = snprintf(buffer, sz, "%s,%s,%s,%s,%s",
				  manufacturer, type, model, version,
				  authorization);
	else
		nbytes = snprintf(buffer, sz, "%s,%s,%s", manufacturer, type,
				  model);
	return (nbytes >= sz) ? ENOBUFS : 0;
}