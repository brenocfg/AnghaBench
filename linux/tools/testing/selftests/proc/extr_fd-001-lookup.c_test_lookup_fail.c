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
struct stat {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int lstat (char const*,struct stat*) ; 

__attribute__((used)) static void test_lookup_fail(const char *pathname)
{
	struct stat st;
	ssize_t rv;

	rv = lstat(pathname, &st);
	assert(rv == -1 && errno == ENOENT);
}