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
typedef  int /*<<< orphan*/  uleds_dev ;
struct uleds_user_dev {int max_brightness; int /*<<< orphan*/  name; } ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  brightness ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  LED_MAX_NAME_SIZE ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int read (int,int*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int write (int,struct uleds_user_dev*,int) ; 

int main(int argc, char const *argv[])
{
	struct uleds_user_dev uleds_dev;
	int fd, ret;
	int brightness;
	struct timespec ts;

	if (argc != 2) {
		fprintf(stderr, "Requires <device-name> argument\n");
		return 1;
	}

	strncpy(uleds_dev.name, argv[1], LED_MAX_NAME_SIZE);
	uleds_dev.max_brightness = 100;

	fd = open("/dev/uleds", O_RDWR);
	if (fd == -1) {
		perror("Failed to open /dev/uleds");
		return 1;
	}

	ret = write(fd, &uleds_dev, sizeof(uleds_dev));
	if (ret == -1) {
		perror("Failed to write to /dev/uleds");
		close(fd);
		return 1;
	}

	while (1) {
		ret = read(fd, &brightness, sizeof(brightness));
		if (ret == -1) {
			perror("Failed to read from /dev/uleds");
			close(fd);
			return 1;
		}
		clock_gettime(CLOCK_MONOTONIC, &ts);
		printf("[%ld.%09ld] %u\n", ts.tv_sec, ts.tv_nsec, brightness);
	}

	close(fd);

	return 0;
}