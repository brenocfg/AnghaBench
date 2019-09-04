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
struct zr36016 {int xdec; int ydec; scalar_t__ yoff; scalar_t__ xoff; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  name; } ;
struct videocodec {scalar_t__ data; } ;
struct vfe_settings {int decimation; scalar_t__ y; int /*<<< orphan*/  x; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct vfe_polarity {int dummy; } ;
struct tvnorm {int HStart; scalar_t__ VStart; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
zr36016_set_video (struct videocodec   *codec,
		   struct tvnorm       *norm,
		   struct vfe_settings *cap,
		   struct vfe_polarity *pol)
{
	struct zr36016 *ptr = (struct zr36016 *) codec->data;

	dprintk(2, "%s: set_video %d.%d, %d/%d-%dx%d (0x%x) call\n",
		ptr->name, norm->HStart, norm->VStart,
		cap->x, cap->y, cap->width, cap->height,
		cap->decimation);

	/* if () return -EINVAL;
	 * trust the master driver that it knows what it does - so
	 * we allow invalid startx/y for now ... */
	ptr->width = cap->width;
	ptr->height = cap->height;
	/* (Ronald) This is ugly. zoran_device.c, line 387
	 * already mentions what happens if HStart is even
	 * (blue faces, etc., cr/cb inversed). There's probably
	 * some good reason why HStart is 0 instead of 1, so I'm
	 * leaving it to this for now, but really... This can be
	 * done a lot simpler */
	ptr->xoff = (norm->HStart ? norm->HStart : 1) + cap->x;
	/* Something to note here (I don't understand it), setting
	 * VStart too high will cause the codec to 'not work'. I
	 * really don't get it. values of 16 (VStart) already break
	 * it here. Just '0' seems to work. More testing needed! */
	ptr->yoff = norm->VStart + cap->y;
	/* (Ronald) dzjeeh, can't this thing do hor_decimation = 4? */
	ptr->xdec = ((cap->decimation & 0xff) == 1) ? 0 : 1;
	ptr->ydec = (((cap->decimation >> 8) & 0xff) == 1) ? 0 : 1;

	return 0;
}