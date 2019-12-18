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
 int /*<<< orphan*/  DPRINTF_S (int /*<<< orphan*/ ) ; 
 size_t STR_TMPFILE ; 
 scalar_t__ TMP_LEN_MAX ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ g_tmpfpath ; 
 scalar_t__ g_tmpfplen ; 
 int /*<<< orphan*/ * messages ; 
 int mkstemp (scalar_t__) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrlcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int create_tmp_file(void)
{
	xstrlcpy(g_tmpfpath + g_tmpfplen - 1, messages[STR_TMPFILE], TMP_LEN_MAX - g_tmpfplen);

	int fd = mkstemp(g_tmpfpath);

	if (fd == -1) {
		DPRINTF_S(strerror(errno));
	}

	return fd;
}