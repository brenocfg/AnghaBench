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
#define  OPTERRARG 130 
#define  OPTERRCOLON 129 
#define  OPTERRNF 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int php_opt_error(int argc, char * const *argv, int oint, int optchr, int err, int show_err) /* {{{ */
{
	if (show_err)
	{
		fprintf(stderr, "Error in argument %d, char %d: ", oint, optchr+1);
		switch(err)
		{
		case OPTERRCOLON:
			fprintf(stderr, ": in flags\n");
			break;
		case OPTERRNF:
			fprintf(stderr, "option not found %c\n", argv[oint][optchr]);
			break;
		case OPTERRARG:
			fprintf(stderr, "no argument for option %c\n", argv[oint][optchr]);
			break;
		default:
			fprintf(stderr, "unknown\n");
			break;
		}
	}
	return('?');
}