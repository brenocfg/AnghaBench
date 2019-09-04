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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  ev_bits ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int ABS_MT_POSITION_X ; 
 int ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  EVIOCGBIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EV_ABS ; 
 int KEY_MAX ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dirfd (int /*<<< orphan*/ *) ; 
 int ioctl (int,int /*<<< orphan*/ ,unsigned char*) ; 
 int openat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int find_dev() {
  int err;

  int ret = -1;

  DIR *dir = opendir("/dev/input");
  assert(dir);
  struct dirent* de = NULL;
  while ((de = readdir(dir))) {
    if (strncmp(de->d_name, "event", 5)) continue;

    int fd = openat(dirfd(dir), de->d_name, O_RDONLY);
    assert(fd >= 0);

    unsigned char ev_bits[KEY_MAX / 8 + 1];
    err = ioctl(fd, EVIOCGBIT(EV_ABS, sizeof(ev_bits)), ev_bits);
    assert(err >= 0);

    const int x_key = ABS_MT_POSITION_X / 8;
    const int y_key = ABS_MT_POSITION_Y / 8;
    if ((ev_bits[x_key] & (ABS_MT_POSITION_X - x_key)) &&
        (ev_bits[y_key] & (ABS_MT_POSITION_Y - y_key))) {
      ret = fd;
      break;
    }
    close(fd);
  }
  closedir(dir);

  return ret;
}