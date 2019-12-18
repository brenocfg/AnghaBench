#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_5__ {int /*<<< orphan*/  tif_clientdata; } ;
struct TYPE_4__ {int bitspersample; int /*<<< orphan*/ ** PALmap; TYPE_3__* tif; int /*<<< orphan*/ * bluecmap; int /*<<< orphan*/ * greencmap; int /*<<< orphan*/ * redcmap; } ;
typedef  int /*<<< orphan*/  TIFFRGBValue ;
typedef  TYPE_1__ TIFFRGBAImage ;

/* Variables and functions */
 int /*<<< orphan*/  CMAP (int) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TIFFFileName (TYPE_3__*) ; 
 scalar_t__ _TIFFmalloc (int) ; 

__attribute__((used)) static int
makecmap(TIFFRGBAImage* img)
{
    int bitspersample = img->bitspersample;
    int nsamples = 8 / bitspersample;
    uint16* r = img->redcmap;
    uint16* g = img->greencmap;
    uint16* b = img->bluecmap;
    uint32 *p;
    int i;

    img->PALmap = (uint32**) _TIFFmalloc(
	256*sizeof (uint32 *)+(256*nsamples*sizeof(uint32)));
    if (img->PALmap == NULL) {
		TIFFErrorExt(img->tif->tif_clientdata, TIFFFileName(img->tif), "No space for Palette mapping table");
		return (0);
	}
    p = (uint32*)(img->PALmap + 256);
    for (i = 0; i < 256; i++) {
	TIFFRGBValue c;
	img->PALmap[i] = p;
#define	CMAP(x)	c = (TIFFRGBValue) x; *p++ = PACK(r[c]&0xff, g[c]&0xff, b[c]&0xff);
	switch (bitspersample) {
	case 1:
	    CMAP(i>>7);
	    CMAP((i>>6)&1);
	    CMAP((i>>5)&1);
	    CMAP((i>>4)&1);
	    CMAP((i>>3)&1);
	    CMAP((i>>2)&1);
	    CMAP((i>>1)&1);
	    CMAP(i&1);
	    break;
	case 2:
	    CMAP(i>>6);
	    CMAP((i>>4)&3);
	    CMAP((i>>2)&3);
	    CMAP(i&3);
	    break;
	case 4:
	    CMAP(i>>4);
	    CMAP(i&0xf);
	    break;
	case 8:
	    CMAP(i);
	    break;
	}
#undef CMAP
    }
    return (1);
}