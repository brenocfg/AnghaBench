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

/* Variables and functions */
 int INT_MAX ; 
 int INT_MIN ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  test_lookup_fail (int,char*) ; 

__attribute__((used)) static void test_lookup(int fd)
{
	char buf[64];
	unsigned int u;
	int i;

	for (i = INT_MIN; i < INT_MIN + 1024; i++) {
		snprintf(buf, sizeof(buf), "%d", i);
		test_lookup_fail(fd, buf);
	}
	for (i = -1024; i < 1024; i++) {
		snprintf(buf, sizeof(buf), "%d", i);
		test_lookup_fail(fd, buf);
	}
	for (u = INT_MAX - 1024; u < (unsigned int)INT_MAX + 1024; u++) {
		snprintf(buf, sizeof(buf), "%u", u);
		test_lookup_fail(fd, buf);
	}
	for (u = UINT_MAX - 1024; u != 0; u++) {
		snprintf(buf, sizeof(buf), "%u", u);
		test_lookup_fail(fd, buf);
	}
}