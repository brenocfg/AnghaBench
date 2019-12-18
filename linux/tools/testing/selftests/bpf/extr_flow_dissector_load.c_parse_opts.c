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
 int cfg_attach ; 
 void* cfg_path_name ; 
 void* cfg_section_name ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int getopt (int,char**,char*) ; 
 void* optarg ; 

__attribute__((used)) static void parse_opts(int argc, char **argv)
{
	bool attach = false;
	bool detach = false;
	int c;

	while ((c = getopt(argc, argv, "adp:s:")) != -1) {
		switch (c) {
		case 'a':
			if (detach)
				error(1, 0, "attach/detach are exclusive");
			attach = true;
			break;
		case 'd':
			if (attach)
				error(1, 0, "attach/detach are exclusive");
			detach = true;
			break;
		case 'p':
			if (cfg_path_name)
				error(1, 0, "only one prog name can be given");

			cfg_path_name = optarg;
			break;
		case 's':
			if (cfg_section_name)
				error(1, 0, "only one section can be given");

			cfg_section_name = optarg;
			break;
		}
	}

	if (detach)
		cfg_attach = false;

	if (cfg_attach && !cfg_path_name)
		error(1, 0, "must provide a path to the BPF program");

	if (cfg_attach && !cfg_section_name)
		error(1, 0, "must provide a section name");
}