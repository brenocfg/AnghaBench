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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dirfd (int /*<<< orphan*/ *) ; 
 int readlinkat (int /*<<< orphan*/ ,char const*,char*,int) ; 

__attribute__((used)) static void f_lnk(DIR *d, const char *filename)
{
	char buf[4096];
	ssize_t rv;

	rv = readlinkat(dirfd(d), filename, buf, sizeof(buf));
	assert((0 <= rv && rv <= sizeof(buf)) || rv == -1);
}