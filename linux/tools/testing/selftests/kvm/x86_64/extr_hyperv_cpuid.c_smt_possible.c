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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int smt_possible(void)
{
	char buf[16];
	FILE *f;
	bool res = 1;

	f = fopen("/sys/devices/system/cpu/smt/control", "r");
	if (f) {
		if (fread(buf, sizeof(*buf), sizeof(buf), f) > 0) {
			if (!strncmp(buf, "forceoff", 8) ||
			    !strncmp(buf, "notsupported", 12))
				res = 0;
		}
		fclose(f);
	}

	return res;
}