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
typedef  int /*<<< orphan*/  gdImagePtr ;
typedef  int /*<<< orphan*/  gdIOCtx ;

/* Variables and functions */
 int /*<<< orphan*/  GD2_DBG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _gdGetColors (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gdGetWord (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdImageCreate (int,int) ; 
 int /*<<< orphan*/  gdImageCreateTrueColor (int,int) ; 
 int /*<<< orphan*/  gdImageDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static gdImagePtr _gdCreateFromFile (gdIOCtx * in, int *sx, int *sy)
{
	gdImagePtr im;
	int gd2xFlag = 0;
	int trueColorFlag = 0;

	if (!gdGetWord(sx, in)) {
		goto fail1;
	}
	if (*sx == 65535 || *sx == 65534) {
		/* This is a gd 2.0 .gd file */
		gd2xFlag = 1;
		/* 2.0.12: 65534 signals a truecolor .gd file. There is a slight redundancy here but we can live with it. */
		if (*sx == 65534) {
			trueColorFlag = 1;
		}
		if (!gdGetWord(sx, in)) {
			goto fail1;
		}
	}
	if (!gdGetWord(sy, in)) {
		goto fail1;
	}

	GD2_DBG(printf("Image is %dx%d\n", *sx, *sy));

	if (trueColorFlag) {
		im = gdImageCreateTrueColor(*sx, *sy);
	} else {
		im = gdImageCreate(*sx, *sy);
	}
	if(!im) {
		goto fail1;
	}
	if (!_gdGetColors(in, im, gd2xFlag)) {
		goto fail2;
	}

	return im;
fail2:
	gdImageDestroy(im);
fail1:
	return 0;
}