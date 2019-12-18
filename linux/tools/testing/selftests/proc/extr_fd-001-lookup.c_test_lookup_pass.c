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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_lookup_pass(const char *pathname)
{
	struct stat st;
	ssize_t rv;

	memset(&st, 0, sizeof(struct stat));
	rv = lstat(pathname, &st);
	assert(rv == 0);
	assert(S_ISLNK(st.st_mode));
}