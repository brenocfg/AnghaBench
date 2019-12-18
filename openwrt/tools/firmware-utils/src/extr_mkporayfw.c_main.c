#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* file_name; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  basename (char*) ; 
 void* board_id ; 
 int build_fw () ; 
 int check_options () ; 
 int extract ; 
 TYPE_1__ firmware_info ; 
 int getopt (int,char**,char*) ; 
 int inspect ; 
 int inspect_fw () ; 
 void* layout_id ; 
 void* ofname ; 
 void* opt_hw_id ; 
 void* optarg ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  usage (int) ; 

int main(int argc, char *argv[])
{
	int ret = EXIT_FAILURE;

	progname = basename(argv[0]);

	int c;

	while ((c = getopt(argc, argv, "B:H:F:f:o:ixh")) != -1) {
		switch (c) {
		case 'B':
			board_id = optarg;
			break;
		case 'H':
			opt_hw_id = optarg;
			break;
		case 'F':
			layout_id = optarg;
			break;
		case 'f':
			firmware_info.file_name = optarg;
			break;
		case 'o':
			ofname = optarg;
			break;
		case 'i':
			inspect = 1;
			break;
		case 'x':
			inspect = 1;
			extract = 1;
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		default:
			usage(EXIT_FAILURE);
			break;
		}
	}

	ret = check_options();
	if (ret) {
		goto out;
	}
	if (!inspect) {
		ret = build_fw();
	} else {
		ret = inspect_fw();
	}

 out:
	return ret;
}