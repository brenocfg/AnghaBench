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
typedef  int /*<<< orphan*/  video_dev ;
struct v4l2_tuner {char* driver; int type; int rangelow; int rangehigh; } ;
struct v4l2_capability {char* driver; int type; int rangelow; int rangehigh; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  VIDIOC_G_TUNER ; 
 int /*<<< orphan*/  VIDIOC_QUERYCAP ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct v4l2_tuner*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int rand () ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int main(int argc, char **argv)
{
	int opt;
	char video_dev[256];
	int count;
	struct v4l2_tuner vtuner;
	struct v4l2_capability vcap;
	int ret;
	int fd;

	if (argc < 2) {
		printf("Usage: %s [-d </dev/videoX>]\n", argv[0]);
		exit(-1);
	}

	/* Process arguments */
	while ((opt = getopt(argc, argv, "d:")) != -1) {
		switch (opt) {
		case 'd':
			strncpy(video_dev, optarg, sizeof(video_dev) - 1);
			video_dev[sizeof(video_dev)-1] = '\0';
			break;
		default:
			printf("Usage: %s [-d </dev/videoX>]\n", argv[0]);
			exit(-1);
		}
	}

	/* Generate random number of interations */
	srand((unsigned int) time(NULL));
	count = rand();

	/* Open Video device and keep it open */
	fd = open(video_dev, O_RDWR);
	if (fd == -1) {
		printf("Video Device open errno %s\n", strerror(errno));
		exit(-1);
	}

	printf("\nNote:\n"
	       "While test is running, remove the device or unbind\n"
	       "driver and ensure there are no use after free errors\n"
	       "and other Oops in the dmesg. When possible, enable KaSan\n"
	       "kernel config option for use-after-free error detection.\n\n");

	while (count > 0) {
		ret = ioctl(fd, VIDIOC_QUERYCAP, &vcap);
		if (ret < 0)
			printf("VIDIOC_QUERYCAP errno %s\n", strerror(errno));
		else
			printf("Video device driver %s\n", vcap.driver);

		ret = ioctl(fd, VIDIOC_G_TUNER, &vtuner);
		if (ret < 0)
			printf("VIDIOC_G_TUNER, errno %s\n", strerror(errno));
		else
			printf("type %d rangelow %d rangehigh %d\n",
				vtuner.type, vtuner.rangelow, vtuner.rangehigh);
		sleep(10);
		count--;
	}
}