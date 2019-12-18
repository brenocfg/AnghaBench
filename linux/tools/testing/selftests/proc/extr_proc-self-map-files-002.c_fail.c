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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int readlink (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,unsigned long,unsigned long) ; 

__attribute__((used)) static void fail(const char *fmt, unsigned long a, unsigned long b)
{
	char name[64];
	char buf[64];

	snprintf(name, sizeof(name), fmt, a, b);
	if (readlink(name, buf, sizeof(buf)) == -1 && errno == ENOENT)
		return;
	exit(1);
}