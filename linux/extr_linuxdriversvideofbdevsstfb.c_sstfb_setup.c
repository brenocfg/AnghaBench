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
 int clipping ; 
 int /*<<< orphan*/  f_ddprintk (char*,char*) ; 
 void* gfxclk ; 
 void* mem ; 
 char* mode_option ; 
 void* simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int slowpci ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strsep (char**,char*) ; 
 int vgapass ; 

__attribute__((used)) static int sstfb_setup(char *options)
{
	char *this_opt;

	if (!options || !*options)
		return 0;

	while ((this_opt = strsep(&options, ",")) != NULL) {
		if (!*this_opt) continue;

		f_ddprintk("option %s\n", this_opt);

		if (!strcmp(this_opt, "vganopass"))
			vgapass = 0;
		else if (!strcmp(this_opt, "vgapass"))
			vgapass = 1;
		else if (!strcmp(this_opt, "clipping"))
		        clipping = 1;
		else if (!strcmp(this_opt, "noclipping"))
		        clipping = 0;
		else if (!strcmp(this_opt, "fastpci"))
		        slowpci = 0;
		else if (!strcmp(this_opt, "slowpci"))
		        slowpci = 1;
		else if (!strncmp(this_opt, "mem:",4))
			mem = simple_strtoul (this_opt+4, NULL, 0);
		else if (!strncmp(this_opt, "gfxclk:",7))
			gfxclk = simple_strtoul (this_opt+7, NULL, 0);
		else
			mode_option = this_opt;
	}
	return 0;
}