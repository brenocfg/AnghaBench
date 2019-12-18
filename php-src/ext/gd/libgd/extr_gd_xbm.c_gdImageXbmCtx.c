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
 int /*<<< orphan*/  efree (char*) ; 
 char* estrdup (char*) ; 
 int /*<<< orphan*/  gdCtxPrintf (int /*<<< orphan*/ *,char*,...) ; 
 int gdImageGetPixel (int /*<<< orphan*/ ,int,int) ; 
 int gdImageSX (int /*<<< orphan*/ ) ; 
 int gdImageSY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  islower (char) ; 
 int /*<<< orphan*/  isupper (char) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 size_t strlen (char*) ; 
 char* strrchr (char*,char) ; 

void gdImageXbmCtx(gdImagePtr image, char* file_name, int fg, gdIOCtx * out)
{
	int x, y, c, b, sx, sy, p;
	char *name, *f;
	size_t i, l;

	name = file_name;
	if ((f = strrchr(name, '/')) != NULL) name = f+1;
	if ((f = strrchr(name, '\\')) != NULL) name = f+1;
	name = estrdup(name);
	if ((f = strrchr(name, '.')) != NULL && !strcasecmp(f, ".XBM")) *f = '\0';
	if ((l = strlen(name)) == 0) {
		efree(name);
		name = estrdup("image");
	} else {
		for (i=0; i<l; i++) {
			/* only in C-locale isalnum() would work */
			if (!isupper(name[i]) && !islower(name[i]) && !isdigit(name[i])) {
				name[i] = '_';
			}
		}
	}

	gdCtxPrintf(out, "#define %s_width %d\n", name, gdImageSX(image));
	gdCtxPrintf(out, "#define %s_height %d\n", name, gdImageSY(image));
	gdCtxPrintf(out, "static unsigned char %s_bits[] = {\n  ", name);

	efree(name);

	b = 1;
	p = 0;
	c = 0;
	sx = gdImageSX(image);
	sy = gdImageSY(image);
	for (y = 0; y < sy; y++) {
		for (x = 0; x < sx; x++) {
			if (gdImageGetPixel(image, x, y) == fg) {
				c |= b;
			}
			if ((b == 128) || (x == sx - 1)) {
				b = 1;
				if (p) {
					gdCtxPrintf(out, ", ");
					if (!(p%12)) {
						gdCtxPrintf(out, "\n  ");
						p = 12;
					}
				}
				p++;
				gdCtxPrintf(out, "0x%02X", c);
				c = 0;
			} else {
				b <<= 1;
			}
		}
	}
	gdCtxPrintf(out, "};\n");
}