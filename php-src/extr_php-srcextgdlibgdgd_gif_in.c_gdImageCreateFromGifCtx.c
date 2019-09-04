#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
typedef  int /*<<< orphan*/  gdIOCtxPtr ;
struct TYPE_7__ {int colorsTotal; scalar_t__* open; void* interlace; } ;

/* Variables and functions */
 void* BitSet (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DoExtension (int /*<<< orphan*/ ,unsigned char,int*,int*) ; 
 int FALSE ; 
 int /*<<< orphan*/  INTERLACE ; 
 int LM_to_uint (unsigned char,unsigned char) ; 
 int /*<<< orphan*/  LOCALCOLORMAP ; 
 int MAXCOLORMAPSIZE ; 
 scalar_t__ ReadColorMap (int /*<<< orphan*/ ,int,unsigned char**) ; 
 int /*<<< orphan*/  ReadImage (TYPE_1__*,int /*<<< orphan*/ ,int,int,unsigned char**,void*,int*) ; 
 int /*<<< orphan*/  ReadOK (int /*<<< orphan*/ ,unsigned char*,int) ; 
 scalar_t__ VERBOSE ; 
 int /*<<< orphan*/  gdImageColorTransparent (TYPE_1__*,int) ; 
 TYPE_1__* gdImageCreate (int,int) ; 
 int /*<<< orphan*/  gdImageDestroy (TYPE_1__*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

gdImagePtr gdImageCreateFromGifCtx(gdIOCtxPtr fd) /* {{{ */
{
	int BitPixel;
#if 0
	int ColorResolution;
	int Background;
	int AspectRatio;
#endif
	int Transparent = (-1);
	unsigned char   buf[16];
	unsigned char   c;
	unsigned char   ColorMap[3][MAXCOLORMAPSIZE];
	unsigned char   localColorMap[3][MAXCOLORMAPSIZE];
	int             imw, imh, screen_width, screen_height;
	int             useGlobalColormap;
	int             bitPixel;
	int	       i;
	/*1.4//int             imageCount = 0; */

	int ZeroDataBlock = FALSE;
	int haveGlobalColormap;
	gdImagePtr im = 0;

	memset(ColorMap, 0, 3 * MAXCOLORMAPSIZE);
	memset(localColorMap, 0, 3 * MAXCOLORMAPSIZE);

	/*1.4//imageNumber = 1; */
	if (! ReadOK(fd,buf,6)) {
		return 0;
	}
	if (strncmp((char *)buf,"GIF",3) != 0) {
		return 0;
	}

	if (memcmp((char *)buf+3, "87a", 3) == 0) {
		/* GIF87a */
	} else if (memcmp((char *)buf+3, "89a", 3) == 0) {
		/* GIF89a */
	} else {
		return 0;
	}

	if (! ReadOK(fd,buf,7)) {
		return 0;
	}

	BitPixel        = 2<<(buf[4]&0x07);
#if 0
	ColorResolution = (int) (((buf[4]&0x70)>>3)+1);
	Background      = buf[5];
	AspectRatio     = buf[6];
#endif
	screen_width = imw = LM_to_uint(buf[0],buf[1]);
	screen_height = imh = LM_to_uint(buf[2],buf[3]);

	haveGlobalColormap = BitSet(buf[4], LOCALCOLORMAP);    /* Global Colormap */
	if (haveGlobalColormap) {
		if (ReadColorMap(fd, BitPixel, ColorMap)) {
			return 0;
		}
	}

	for (;;) {
		int top, left;
		int width, height;

		if (! ReadOK(fd,&c,1)) {
			return 0;
		}
		if (c == ';') {         /* GIF terminator */
			goto terminated;
		}

		if (c == '!') {         /* Extension */
			if (! ReadOK(fd,&c,1)) {
				return 0;
			}
			DoExtension(fd, c, &Transparent, &ZeroDataBlock);
			continue;
		}

		if (c != ',') {         /* Not a valid start character */
			continue;
		}

		/*1.4//++imageCount; */

		if (! ReadOK(fd,buf,9)) {
			return 0;
		}

		useGlobalColormap = ! BitSet(buf[8], LOCALCOLORMAP);

		bitPixel = 1<<((buf[8]&0x07)+1);
		left = LM_to_uint(buf[0], buf[1]);
		top = LM_to_uint(buf[2], buf[3]);
		width = LM_to_uint(buf[4], buf[5]);
		height = LM_to_uint(buf[6], buf[7]);

		if (left + width > screen_width || top + height > screen_height) {
			if (VERBOSE) {
				printf("Frame is not confined to screen dimension.\n");
			}
			return 0;
		}

		if (!(im = gdImageCreate(width, height))) {
			return 0;
		}
		im->interlace = BitSet(buf[8], INTERLACE);
		if (!useGlobalColormap) {
			if (ReadColorMap(fd, bitPixel, localColorMap)) {
				gdImageDestroy(im);
				return 0;
			}
			ReadImage(im, fd, width, height, localColorMap,
					BitSet(buf[8], INTERLACE), &ZeroDataBlock);
		} else {
			if (!haveGlobalColormap) {
				gdImageDestroy(im);
				return 0;
			}
			ReadImage(im, fd, width, height,
						ColorMap,
						BitSet(buf[8], INTERLACE), &ZeroDataBlock);
		}
		if (Transparent != (-1)) {
			gdImageColorTransparent(im, Transparent);
		}
		goto terminated;
	}

terminated:
	/* Terminator before any image was declared! */
	if (!im) {
		return 0;
	}
	/* Check for open colors at the end, so
	   we can reduce colorsTotal and ultimately
	   BitsPerPixel */
	for (i=((im->colorsTotal-1)); (i>=0); i--) {
		if (im->open[i]) {
			im->colorsTotal--;
		} else {
			break;
		}
	}
	if (!im->colorsTotal) {
		gdImageDestroy(im);
		return 0;
	}
	return im;
}