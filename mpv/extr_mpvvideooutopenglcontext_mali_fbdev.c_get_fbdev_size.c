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
struct fb_var_screeninfo {int xres; int yres; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBIOGET_VSCREENINFO ; 
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,struct fb_var_screeninfo*) ; 
 int open (char*,int) ; 

__attribute__((used)) static bool get_fbdev_size(int *w, int *h)
{
    int fd = open("/dev/fb0", O_RDWR | O_CLOEXEC);
    if (fd < 0)
        return false;

    struct fb_var_screeninfo info = {0};
    bool ok = !ioctl(fd, FBIOGET_VSCREENINFO, &info);
    if (ok) {
        *w = info.xres;
        *h = info.yres;
    }

    close(fd);

    return ok;
}