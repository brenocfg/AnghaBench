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
struct dirent {scalar_t__ d_type; int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fdopendir (int) ; 
 int streq (int /*<<< orphan*/ ,char*) ; 
 struct dirent* xreaddir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_readdir(int fd)
{
	DIR *d;
	struct dirent *de;

	d = fdopendir(fd);
	assert(d);

	de = xreaddir(d);
	assert(streq(de->d_name, "."));
	assert(de->d_type == DT_DIR);

	de = xreaddir(d);
	assert(streq(de->d_name, ".."));
	assert(de->d_type == DT_DIR);

	de = xreaddir(d);
	assert(!de);
}