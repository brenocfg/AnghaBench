#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timespec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdd; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dirfd (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 TYPE_1__ options ; 
 int utimensat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pifs_utimens(const char *path, const struct timespec times[2])
{
  DIR *dir = opendir(options.mdd);
  if (!dir) {
    return -errno;
  }
  int ret = utimensat(dirfd(dir), basename((char *) path), times, 0);
  closedir(dir);
  return ret == -1 ? -errno : ret;
}