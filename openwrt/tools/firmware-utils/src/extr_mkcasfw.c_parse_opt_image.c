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
struct image_desc {int /*<<< orphan*/ * file_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int ERR_FATAL ; 
 int MAX_ARG_COUNT ; 
 int MAX_ARG_LEN ; 
 int /*<<< orphan*/  WARN (char*) ; 
 struct image_desc fs_image ; 
 int /*<<< orphan*/  is_empty_arg (char*) ; 
 struct image_desc kernel_image ; 
 int parse_arg (char*,char*,char**) ; 
 int /*<<< orphan*/ * strdup (char*) ; 

int
parse_opt_image(char ch, char *arg)
{
	char buf[MAX_ARG_LEN];
	char *argv[MAX_ARG_COUNT];
	int argc;
	char *p;
	struct image_desc *desc = NULL;
	int i;

	switch (ch) {
	case 'K':
		if (kernel_image.file_name) {
			WARN("only one kernel option allowed");
			break;
		}
		desc = &kernel_image;
		break;
	case 'F':
		if (fs_image.file_name) {
			WARN("only one fs option allowed");
			break;
		}
		desc = &fs_image;
		break;
	}

	if (!desc)
		return ERR_FATAL;

	argc = parse_arg(arg, buf, argv);

	i = 0;
	p = argv[i++];
	if (!is_empty_arg(p)) {
		desc->file_name = strdup(p);
		if (desc->file_name == NULL) {
			ERR("not enough memory");
			return ERR_FATAL;
		}
	} else {
		ERR("no file specified for option %c", ch);
		return ERR_FATAL;
	}

	return 0;
}