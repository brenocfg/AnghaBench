#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char identsize; unsigned char colormaptype; unsigned char imagetype; unsigned char colormapstart; unsigned char colormaplength; unsigned char colormapbits; unsigned char xstart; unsigned char ystart; unsigned char width; unsigned char height; unsigned char bits; unsigned char alphabits; int fliph; int flipv; char* ident; } ;
typedef  TYPE_1__ oTga ;
typedef  int /*<<< orphan*/  header ;
typedef  int /*<<< orphan*/  gdIOCtx ;

/* Variables and functions */
 int /*<<< orphan*/  GD_WARNING ; 
 int TGA_BPP_24 ; 
 int TGA_BPP_32 ; 
 int gdGetBuf (unsigned char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ gdMalloc (int) ; 
 int /*<<< orphan*/  gd_error (char*) ; 
 int /*<<< orphan*/  gd_error_ex (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

int read_header_tga(gdIOCtx *ctx, oTga *tga)
{

	unsigned char header[18];

	if (gdGetBuf(header, sizeof(header), ctx) < 18) {
		gd_error("fail to read header");
		return -1;
	}

	tga->identsize = header[0];
	tga->colormaptype = header[1];
	tga->imagetype = header[2];
	tga->colormapstart = header[3] + (header[4] << 8);
	tga->colormaplength = header[5] + (header[6] << 8);
	tga->colormapbits = header[7];
	tga->xstart = header[8] + (header[9] << 8);
	tga->ystart = header[10] + (header[11] << 8);
	tga->width = header[12] + (header[13] << 8);
	tga->height = header[14] + (header[15] << 8);
	tga->bits = header[16];
	tga->alphabits = header[17] & 0x0f;
	tga->fliph = (header[17] & 0x10) ? 1 : 0;
	tga->flipv = (header[17] & 0x20) ? 0 : 1;

#if DEBUG
	printf("format bps: %i\n", tga->bits);
	printf("flip h/v: %i / %i\n", tga->fliph, tga->flipv);
	printf("alpha: %i\n", tga->alphabits);
	printf("wxh: %i %i\n", tga->width, tga->height);
#endif

	if (!((tga->bits == TGA_BPP_24 && tga->alphabits == 0)
		|| (tga->bits == TGA_BPP_32 && tga->alphabits == 8)))
	{
		gd_error_ex(GD_WARNING, "gd-tga: %u bits per pixel with %u alpha bits not supported\n",
			tga->bits, tga->alphabits);
		return -1;
	}

	tga->ident = NULL;

	if (tga->identsize > 0) {
		tga->ident = (char *) gdMalloc(tga->identsize * sizeof(char));
		if(tga->ident == NULL) {
			return -1;
		}

		gdGetBuf(tga->ident, tga->identsize, ctx);
	}

	return 1;
}