#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gdImagePtr ;
typedef  int /*<<< orphan*/  gdIOCtx ;
struct TYPE_5__ {int /*<<< orphan*/ * bitmap; } ;
typedef  TYPE_1__ Wbmp ;

/* Variables and functions */
 int /*<<< orphan*/  WBMP_BLACK ; 
 int /*<<< orphan*/  WBMP_WHITE ; 
 TYPE_1__* createwbmp (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freewbmp (TYPE_1__*) ; 
 int gdImageGetPixel (int /*<<< orphan*/ ,int,int) ; 
 int gdImageSX (int /*<<< orphan*/ ) ; 
 int gdImageSY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gd_error (char*) ; 
 int /*<<< orphan*/  gd_putout ; 
 scalar_t__ writewbmp (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _gdImageWBMPCtx(gdImagePtr image, int fg, gdIOCtx *out)
{
	int x, y, pos;
	Wbmp *wbmp;

	/* create the WBMP */
	if ((wbmp = createwbmp (gdImageSX (image), gdImageSY (image), WBMP_WHITE)) == NULL) {
		gd_error("Could not create WBMP");
		return 1;
	}

	/* fill up the WBMP structure */
	pos = 0;
	for (y = 0; y < gdImageSY(image); y++) {
		for (x = 0; x < gdImageSX(image); x++) {
			if (gdImageGetPixel (image, x, y) == fg) {
				wbmp->bitmap[pos] = WBMP_BLACK;
			}
			pos++;
		}
	}

	/* write the WBMP to a gd file descriptor */
	if (writewbmp (wbmp, &gd_putout, out)) {
		freewbmp(wbmp);
		gd_error("Could not save WBMP");
		return 1;
	}

	/* des submitted this bugfix: gdFree the memory. */
	freewbmp(wbmp);

	return 0;
}