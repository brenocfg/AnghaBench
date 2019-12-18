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
struct device_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  build_image (char const*,char const*,char const*,unsigned int,int,int,struct device_info*) ; 
 int /*<<< orphan*/  convert_firmware (char const*,char const*) ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  extract_firmware (char const*,char const*) ; 
 struct device_info* find_board (char const*) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 int /*<<< orphan*/  set_source_date_epoch () ; 
 int /*<<< orphan*/  sscanf (char*,char*,unsigned int*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char *argv[]) {
	const char *board = NULL, *kernel_image = NULL, *rootfs_image = NULL, *output = NULL;
	const char *extract_image = NULL, *output_directory = NULL, *convert_image = NULL;
	bool add_jffs2_eof = false, sysupgrade = false;
	unsigned rev = 0;
	struct device_info *info;
	set_source_date_epoch();

	while (true) {
		int c;

		c = getopt(argc, argv, "B:k:r:o:V:jSh:x:d:z:");
		if (c == -1)
			break;

		switch (c) {
		case 'B':
			board = optarg;
			break;

		case 'k':
			kernel_image = optarg;
			break;

		case 'r':
			rootfs_image = optarg;
			break;

		case 'o':
			output = optarg;
			break;

		case 'V':
			sscanf(optarg, "r%u", &rev);
			break;

		case 'j':
			add_jffs2_eof = true;
			break;

		case 'S':
			sysupgrade = true;
			break;

		case 'h':
			usage(argv[0]);
			return 0;

		case 'd':
			output_directory = optarg;
			break;

		case 'x':
			extract_image = optarg;
			break;

		case 'z':
			convert_image = optarg;
			break;

		default:
			usage(argv[0]);
			return 1;
		}
	}

	if (extract_image || output_directory) {
		if (!extract_image)
			error(1, 0, "No factory/oem image given via -x <file>. Output directory is only valid with -x");
		if (!output_directory)
			error(1, 0, "Can not extract an image without output directory. Use -d <dir>");
		extract_firmware(extract_image, output_directory);
	} else if (convert_image) {
		if (!output)
			error(1, 0, "Can not convert a factory/oem image into sysupgrade image without output file. Use -o <file>");
		convert_firmware(convert_image, output);
	} else {
		if (!board)
			error(1, 0, "no board has been specified");
		if (!kernel_image)
			error(1, 0, "no kernel image has been specified");
		if (!rootfs_image)
			error(1, 0, "no rootfs image has been specified");
		if (!output)
			error(1, 0, "no output filename has been specified");

		info = find_board(board);

		if (info == NULL)
			error(1, 0, "unsupported board %s", board);

		build_image(output, kernel_image, rootfs_image, rev, add_jffs2_eof, sysupgrade, info);
	}

	return 0;
}