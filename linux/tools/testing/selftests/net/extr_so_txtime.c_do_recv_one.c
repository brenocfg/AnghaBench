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
struct timed_send {scalar_t__ delay_us; char data; } ;
typedef  int /*<<< orphan*/  rbuf ;
typedef  int int64_t ;

/* Variables and functions */
 int cfg_variance_us ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char,int,int) ; 
 int gettime_ns () ; 
 int glob_tstart ; 
 int labs (int) ; 
 int recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void do_recv_one(int fdr, struct timed_send *ts)
{
	int64_t tstop, texpect;
	char rbuf[2];
	int ret;

	ret = recv(fdr, rbuf, sizeof(rbuf), 0);
	if (ret == -1)
		error(1, errno, "read");
	if (ret != 1)
		error(1, 0, "read: %dB", ret);

	tstop = (gettime_ns() - glob_tstart) / 1000;
	texpect = ts->delay_us >= 0 ? ts->delay_us : 0;

	fprintf(stderr, "payload:%c delay:%ld expected:%ld (us)\n",
			rbuf[0], tstop, texpect);

	if (rbuf[0] != ts->data)
		error(1, 0, "payload mismatch. expected %c", ts->data);

	if (labs(tstop - texpect) > cfg_variance_us)
		error(1, 0, "exceeds variance (%d us)", cfg_variance_us);
}