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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,scalar_t__) ; 
 int /*<<< orphan*/  err (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (scalar_t__,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int getpid () ; 
 scalar_t__ pid_file ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_pid_file(void)
{
	if (pid_file) {
		dbg("creating pid file %s", pid_file);
		FILE *fp;

		fp = fopen(pid_file, "w");
		if (!fp) {
			err("pid_file: %s: %d (%s)",
			    pid_file, errno, strerror(errno));
			return;
		}
		fprintf(fp, "%d\n", getpid());
		fclose(fp);
	}
}