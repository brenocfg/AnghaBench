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

/* Variables and functions */
 int /*<<< orphan*/  MS_BIND ; 
 int do_tiocgptpeer (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int mount (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int verify_ptmx_bind_mount(void)
{
	int ret;

	ret = mount("/dev/pts/ptmx", "/dev/ptmx", NULL, MS_BIND, NULL);
	if (ret < 0) {
		fprintf(stderr, "Failed to bind mount \"/dev/pts/ptmx\" to "
				"\"/dev/ptmx\" mount namespace\n");
		return -1;
	}

	ret = do_tiocgptpeer("/dev/ptmx", "/dev/pts/");
	if (ret < 0)
		return -1;

	return 0;
}