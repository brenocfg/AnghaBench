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
typedef  int __u16 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sprintf (char*,char*,char*,int) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 
 char* token_sysfs ; 

__attribute__((used)) static int find_token(__u16 token, __u16 *location, __u16 *value)
{
	char location_sysfs[60];
	char value_sysfs[57];
	char buf[4096];
	FILE *f;
	int ret;

	ret = sprintf(value_sysfs, "%s/%04x_value", token_sysfs, token);
	if (ret < 0) {
		printf("sprintf value failed\n");
		return 2;
	}
	f = fopen(value_sysfs, "rb");
	if (!f) {
		printf("failed to open %s\n", value_sysfs);
		return 2;
	}
	fread(buf, 1, 4096, f);
	fclose(f);
	*value = (__u16) strtol(buf, NULL, 16);

	ret = sprintf(location_sysfs, "%s/%04x_location", token_sysfs, token);
	if (ret < 0) {
		printf("sprintf location failed\n");
		return 1;
	}
	f = fopen(location_sysfs, "rb");
	if (!f) {
		printf("failed to open %s\n", location_sysfs);
		return 2;
	}
	fread(buf, 1, 4096, f);
	fclose(f);
	*location = (__u16) strtol(buf, NULL, 16);

	if (*location)
		return 0;
	return 2;
}