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
typedef  int /*<<< orphan*/  RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 char* r_str_ichr (char*,char) ; 
 int /*<<< orphan*/  run_new_command (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int run_old_command (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

int run_ioctl_command(RIO *io, RIODesc *iodesc, const char *buf) {
	buf = r_str_ichr ((char *) buf, ' ');

	if (!run_new_command (io, iodesc, buf)) {
		return run_old_command (io, iodesc, buf);
	}
	return 0;
}