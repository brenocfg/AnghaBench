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

/* Variables and functions */
 size_t LINUX_LOGO_CLUT224 ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int logo_clutsize ; 
 int logo_height ; 
 size_t logo_type ; 
 char** logo_types ; 
 int logo_width ; 
 char* logoname ; 
 int /*<<< orphan*/  out ; 
 scalar_t__ outputname ; 

__attribute__((used)) static void write_footer(void)
{
    fputs("\n};\n\n", out);
    fprintf(out, "const struct linux_logo %s __initconst = {\n", logoname);
    fprintf(out, "\t.type\t\t= %s,\n", logo_types[logo_type]);
    fprintf(out, "\t.width\t\t= %d,\n", logo_width);
    fprintf(out, "\t.height\t\t= %d,\n", logo_height);
    if (logo_type == LINUX_LOGO_CLUT224) {
	fprintf(out, "\t.clutsize\t= %d,\n", logo_clutsize);
	fprintf(out, "\t.clut\t\t= %s_clut,\n", logoname);
    }
    fprintf(out, "\t.data\t\t= %s_data\n", logoname);
    fputs("};\n\n", out);

    /* close logo file */
    if (outputname)
	fclose(out);
}