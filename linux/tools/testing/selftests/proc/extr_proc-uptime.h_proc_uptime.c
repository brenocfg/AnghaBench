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
typedef  int uint64_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int pread (int,char*,int,int /*<<< orphan*/ ) ; 
 int xstrtoull (char*,char**) ; 

__attribute__((used)) static void proc_uptime(int fd, uint64_t *uptime, uint64_t *idle)
{
	uint64_t val1, val2;
	char buf[64], *p;
	ssize_t rv;

	/* save "p < end" checks */
	memset(buf, 0, sizeof(buf));
	rv = pread(fd, buf, sizeof(buf), 0);
	assert(0 <= rv && rv <= sizeof(buf));
	buf[sizeof(buf) - 1] = '\0';

	p = buf;

	val1 = xstrtoull(p, &p);
	assert(p[0] == '.');
	assert('0' <= p[1] && p[1] <= '9');
	assert('0' <= p[2] && p[2] <= '9');
	assert(p[3] == ' ');

	val2 = (p[1] - '0') * 10 + p[2] - '0';
	*uptime = val1 * 100 + val2;

	p += 4;

	val1 = xstrtoull(p, &p);
	assert(p[0] == '.');
	assert('0' <= p[1] && p[1] <= '9');
	assert('0' <= p[2] && p[2] <= '9');
	assert(p[3] == '\n');

	val2 = (p[1] - '0') * 10 + p[2] - '0';
	*idle = val1 * 100 + val2;

	assert(p + 4 == buf + rv);
}