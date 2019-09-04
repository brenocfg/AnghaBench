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
typedef  int uint16 ;
struct TYPE_3__ {int* redcmap; int* greencmap; int* bluecmap; long bitspersample; } ;
typedef  TYPE_1__ TIFFRGBAImage ;

/* Variables and functions */

__attribute__((used)) static void
cvtcmap(TIFFRGBAImage* img)
{
    uint16* r = img->redcmap;
    uint16* g = img->greencmap;
    uint16* b = img->bluecmap;
    long i;

    for (i = (1L<<img->bitspersample)-1; i >= 0; i--) {
#define	CVT(x)		((uint16)((x)>>8))
	r[i] = CVT(r[i]);
	g[i] = CVT(g[i]);
	b[i] = CVT(b[i]);
#undef	CVT
    }
}