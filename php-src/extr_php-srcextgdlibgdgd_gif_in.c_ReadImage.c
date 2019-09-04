#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
typedef  int /*<<< orphan*/  gdIOCtx ;
struct TYPE_4__ {unsigned char* red; unsigned char* green; unsigned char* blue; int* open; int colorsTotal; } ;
typedef  int /*<<< orphan*/  LZW_STATIC_DATA ;

/* Variables and functions */
 size_t CM_BLUE ; 
 size_t CM_GREEN ; 
 size_t CM_RED ; 
 int /*<<< orphan*/  FALSE ; 
 int LWZReadByte (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char,int*) ; 
 unsigned char MAX_LWZ_BITS ; 
 int /*<<< orphan*/  ReadOK (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gdImageSetPixel (TYPE_1__*,int,int,int) ; 
 int gdMaxColors ; 

__attribute__((used)) static void
ReadImage(gdImagePtr im, gdIOCtx *fd, int len, int height, unsigned char (*cmap)[256], int interlace, int *ZeroDataBlockP) /*1.4//, int ignore) */
{
	unsigned char   c;
	int             v;
	int             xpos = 0, ypos = 0, pass = 0;
	int i;
	LZW_STATIC_DATA sd;


	/*
	 **  Initialize the Compression routines
	 */
	if (! ReadOK(fd,&c,1)) {
		return;
	}

	if (c > MAX_LWZ_BITS) {
		return;
	}

	/* Stash the color map into the image */
	for (i=0; (i<gdMaxColors); i++) {
		im->red[i] = cmap[CM_RED][i];
		im->green[i] = cmap[CM_GREEN][i];
		im->blue[i] = cmap[CM_BLUE][i];
		im->open[i] = 1;
	}
	/* Many (perhaps most) of these colors will remain marked open. */
	im->colorsTotal = gdMaxColors;
	if (LWZReadByte(fd, &sd, TRUE, c, ZeroDataBlockP) < 0) {
		return;
	}

	/*
	 **  If this is an "uninteresting picture" ignore it.
	 **  REMOVED For 1.4
	 */
	/*if (ignore) { */
	/*        while (LWZReadByte(fd, &sd, FALSE, c) >= 0) */
	/*                ; */
	/*        return; */
	/*} */

	while ((v = LWZReadByte(fd, &sd, FALSE, c, ZeroDataBlockP)) >= 0) {
		if (v >= gdMaxColors) {
			v = 0;
		}
		/* This how we recognize which colors are actually used. */
		if (im->open[v]) {
			im->open[v] = 0;
		}
		gdImageSetPixel(im, xpos, ypos, v);
		++xpos;
		if (xpos == len) {
			xpos = 0;
			if (interlace) {
				switch (pass) {
					case 0:
					case 1:
						ypos += 8; break;
					case 2:
						ypos += 4; break;
					case 3:
						ypos += 2; break;
				}

				if (ypos >= height) {
					++pass;
					switch (pass) {
						case 1:
							ypos = 4; break;
						case 2:
							ypos = 2; break;
						case 3:
							ypos = 1; break;
						default:
							goto fini;
					}
				}
			} else {
				++ypos;
			}
		}
		if (ypos >= height)
			break;
	}

fini:
	if (LWZReadByte(fd, &sd, FALSE, c, ZeroDataBlockP) >=0) {
		/* Ignore extra */
	}
}