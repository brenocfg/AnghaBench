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
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */

void dvd_set_speed(stream_t *stream, char *device, unsigned speed)
{
#if defined(__linux__) && defined(SG_IO) && defined(GPCMD_SET_STREAMING)
  int fd;
  unsigned char buffer[28];
  unsigned char cmd[12];
  struct sg_io_hdr sghdr;
  struct stat st;

  memset(&st, 0, sizeof(st));

  if (stat(device, &st) == -1) return;

  if (!S_ISBLK(st.st_mode)) return; /* not a block device */

  switch (speed) {
  case 0: /* don't touch speed setting */
    return;
  case -1: /* restore default value */
    MP_INFO(stream, "Restoring DVD speed... ");
    break;
  default: /* limit to <speed> KB/s */
    // speed < 100 is multiple of DVD single speed (1350KB/s)
    if (speed < 100)
      speed *= 1350;
    MP_INFO(stream, "Limiting DVD speed to %dKB/s... ", speed);
    break;
  }

  memset(&sghdr, 0, sizeof(sghdr));
  sghdr.interface_id = 'S';
  sghdr.timeout = 5000;
  sghdr.dxfer_direction = SG_DXFER_TO_DEV;
  sghdr.dxfer_len = sizeof(buffer);
  sghdr.dxferp = buffer;
  sghdr.cmd_len = sizeof(cmd);
  sghdr.cmdp = cmd;

  memset(cmd, 0, sizeof(cmd));
  cmd[0] = GPCMD_SET_STREAMING;
  cmd[10] = sizeof(buffer);

  memset(buffer, 0, sizeof(buffer));
  /* first sector 0, last sector 0xffffffff */
  AV_WB32(buffer + 8, 0xffffffff);
  if (speed == -1)
    buffer[0] = 4; /* restore default */
  else {
    /* <speed> kilobyte */
    AV_WB32(buffer + 12, speed);
    AV_WB32(buffer + 20, speed);
  }
  /* 1 second */
  AV_WB16(buffer + 18, 1000);
  AV_WB16(buffer + 26, 1000);

  fd = open(device, O_RDWR | O_NONBLOCK | O_CLOEXEC);
  if (fd == -1) {
    MP_INFO(stream, "Couldn't open DVD device for writing, changing DVD speed needs write access.\n");
    return;
  }

  if (ioctl(fd, SG_IO, &sghdr) < 0)
    MP_INFO(stream, "failed\n");
  else
    MP_INFO(stream, "successful\n");

  close(fd);
#endif
}