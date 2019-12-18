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
struct isst_if_platform_info {int api_version; int driver_version; int mbox_supported; int mmio_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISST_IF_GET_PLATFORM_INFO ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct isst_if_platform_info*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void isst_print_platform_information(void)
{
	struct isst_if_platform_info platform_info;
	const char *pathname = "/dev/isst_interface";
	int fd;

	fd = open(pathname, O_RDWR);
	if (fd < 0)
		err(-1, "%s open failed", pathname);

	if (ioctl(fd, ISST_IF_GET_PLATFORM_INFO, &platform_info) == -1) {
		perror("ISST_IF_GET_PLATFORM_INFO");
	} else {
		fprintf(outf, "Platform: API version : %d\n",
			platform_info.api_version);
		fprintf(outf, "Platform: Driver version : %d\n",
			platform_info.driver_version);
		fprintf(outf, "Platform: mbox supported : %d\n",
			platform_info.mbox_supported);
		fprintf(outf, "Platform: mmio supported : %d\n",
			platform_info.mmio_supported);
	}

	close(fd);

	exit(0);
}