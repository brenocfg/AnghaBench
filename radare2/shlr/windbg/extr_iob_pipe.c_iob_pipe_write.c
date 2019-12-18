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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ EPIPE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 
 int send (int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iob_pipe_write(void *p, const uint8_t *buf, const uint64_t count, const int timeout) {
	int ret = send ((int) (size_t) p, buf, count, 0);
	if (ret < 1) {
		r_sys_perror ("iob_pipe_write, send");
		if (errno == EPIPE) {
			exit (1);
		}
	}
	return ret;
}