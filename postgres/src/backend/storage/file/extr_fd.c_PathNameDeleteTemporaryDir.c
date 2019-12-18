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

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ errno ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  unlink_if_exists_fname ; 
 int /*<<< orphan*/  walkdir (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
PathNameDeleteTemporaryDir(const char *dirname)
{
	struct stat statbuf;

	/* Silently ignore missing directory. */
	if (stat(dirname, &statbuf) != 0 && errno == ENOENT)
		return;

	/*
	 * Currently, walkdir doesn't offer a way for our passed in function to
	 * maintain state.  Perhaps it should, so that we could tell the caller
	 * whether this operation succeeded or failed.  Since this operation is
	 * used in a cleanup path, we wouldn't actually behave differently: we'll
	 * just log failures.
	 */
	walkdir(dirname, unlink_if_exists_fname, false, LOG);
}