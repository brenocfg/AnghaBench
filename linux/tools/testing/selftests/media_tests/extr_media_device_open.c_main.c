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
struct media_device_info {char* model; char* driver; } ;
typedef  int /*<<< orphan*/  media_device ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_IOC_DEVICE_INFO ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ getuid () ; 
 int ioctl (int,int /*<<< orphan*/ ,struct media_device_info*) ; 
 int /*<<< orphan*/  ksft_exit_skip (char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

int main(int argc, char **argv)
{
	int opt;
	char media_device[256];
	int count = 0;
	struct media_device_info mdi;
	int ret;
	int fd;

	if (argc < 2) {
		printf("Usage: %s [-d </dev/mediaX>]\n", argv[0]);
		exit(-1);
	}

	/* Process arguments */
	while ((opt = getopt(argc, argv, "d:")) != -1) {
		switch (opt) {
		case 'd':
			strncpy(media_device, optarg, sizeof(media_device) - 1);
			media_device[sizeof(media_device)-1] = '\0';
			break;
		default:
			printf("Usage: %s [-d </dev/mediaX>]\n", argv[0]);
			exit(-1);
		}
	}

	if (getuid() != 0)
		ksft_exit_skip("Please run the test as root - Exiting.\n");

	/* Open Media device and keep it open */
	fd = open(media_device, O_RDWR);
	if (fd == -1) {
		printf("Media Device open errno %s\n", strerror(errno));
		exit(-1);
	}

	ret = ioctl(fd, MEDIA_IOC_DEVICE_INFO, &mdi);
	if (ret < 0)
		printf("Media Device Info errno %s\n", strerror(errno));
	else
		printf("Media device model %s driver %s\n",
			mdi.model, mdi.driver);
}