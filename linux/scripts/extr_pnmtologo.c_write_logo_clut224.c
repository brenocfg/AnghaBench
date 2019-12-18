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
struct TYPE_5__ {unsigned int red; unsigned int green; unsigned int blue; } ;

/* Variables and functions */
 unsigned int MAX_LINUX_LOGO_COLORS ; 
 int /*<<< orphan*/  die (char*,unsigned int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_equal (TYPE_1__,TYPE_1__) ; 
 TYPE_1__* logo_clut ; 
 unsigned int logo_clutsize ; 
 TYPE_1__** logo_data ; 
 unsigned int logo_height ; 
 unsigned int logo_width ; 
 char* logoname ; 
 int /*<<< orphan*/  out ; 
 int /*<<< orphan*/  write_footer () ; 
 int /*<<< orphan*/  write_header () ; 
 int /*<<< orphan*/  write_hex (unsigned int) ; 
 scalar_t__ write_hex_cnt ; 

__attribute__((used)) static void write_logo_clut224(void)
{
    unsigned int i, j, k;

    /* validate image */
    for (i = 0; i < logo_height; i++)
	for (j = 0; j < logo_width; j++) {
	    for (k = 0; k < logo_clutsize; k++)
		if (is_equal(logo_data[i][j], logo_clut[k]))
		    break;
	    if (k == logo_clutsize) {
		if (logo_clutsize == MAX_LINUX_LOGO_COLORS)
		    die("Image has more than %d colors\n"
			"Use ppmquant(1) to reduce the number of colors\n",
			MAX_LINUX_LOGO_COLORS);
		logo_clut[logo_clutsize++] = logo_data[i][j];
	    }
	}

    /* write file header */
    write_header();

    /* write logo data */
    for (i = 0; i < logo_height; i++)
	for (j = 0; j < logo_width; j++) {
	    for (k = 0; k < logo_clutsize; k++)
		if (is_equal(logo_data[i][j], logo_clut[k]))
		    break;
	    write_hex(k+32);
	}
    fputs("\n};\n\n", out);

    /* write logo clut */
    fprintf(out, "static unsigned char %s_clut[] __initdata = {\n",
	    logoname);
    write_hex_cnt = 0;
    for (i = 0; i < logo_clutsize; i++) {
	write_hex(logo_clut[i].red);
	write_hex(logo_clut[i].green);
	write_hex(logo_clut[i].blue);
    }

    /* write logo structure and file footer */
    write_footer();
}