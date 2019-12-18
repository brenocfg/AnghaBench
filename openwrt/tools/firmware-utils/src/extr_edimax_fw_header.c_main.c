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
 int /*<<< orphan*/  ERR (char*,char*,void*) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  basename (char*) ; 
 int build_fw () ; 
 int check_options () ; 
 int /*<<< orphan*/  end_addr ; 
 int force ; 
 void* fw_version ; 
 int getopt (int,char**,char*) ; 
 void* ifname ; 
 int /*<<< orphan*/  image_type ; 
 void* magic ; 
 void* model ; 
 void* mtd_name ; 
 void* ofname ; 
 void* optarg ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  start_addr ; 
 int /*<<< orphan*/  str2u32 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  str2u8 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage (int) ; 

int main(int argc, char *argv[])
{
	int ret = EXIT_FAILURE;

	progname = basename(argv[0]);

	while (1) {
		int c;

		c = getopt(argc, argv, "e:fhi:o:m:M:n:s:t:v:");
		if (c == -1)
			break;

		switch (c) {
		case 'e':
			if (str2u32(optarg, &end_addr)) {
				ERR("%s is invalid '%s'",
				    "end address", optarg);
				goto out;
			}
			break;
		case 'f':
			force = 1;
			break;
		case 'i':
			ifname = optarg;
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		case 'o':
			ofname = optarg;
			break;
		case 'm':
			model = optarg;
			break;
		case 'M':
			magic = optarg;
			break;
		case 'n':
			mtd_name = optarg;
			break;
		case 's':
			if (str2u32(optarg, &start_addr)) {
				ERR("%s is invalid '%s'",
				    "start address", optarg);
				goto out;
			}
			break;
		case 't':
			if (str2u8(optarg, &image_type)) {
				ERR("%s is invalid '%s'",
				    "image type", optarg);
				goto out;
			}
			break;
		case 'v':
			fw_version = optarg;
			break;
		default:
			usage(EXIT_FAILURE);
			break;
		}
	}

	ret = check_options();
	if (ret)
		goto out;

	ret = build_fw();

out:
	return ret;
}