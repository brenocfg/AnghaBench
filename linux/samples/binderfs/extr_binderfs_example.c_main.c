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
struct binderfs_device {char* name; int major; int minor; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_CTL_ADD ; 
 int /*<<< orphan*/  CLONE_NEWNS ; 
 int EEXIST ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int MS_PRIVATE ; 
 int MS_REC ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct binderfs_device*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int mkdir (char*,int) ; 
 int mount (int /*<<< orphan*/ *,char*,char*,int,int /*<<< orphan*/ ) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int unlink (char*) ; 
 int unshare (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
	int fd, ret, saved_errno;
	size_t len;
	struct binderfs_device device = { 0 };

	ret = unshare(CLONE_NEWNS);
	if (ret < 0) {
		fprintf(stderr, "%s - Failed to unshare mount namespace\n",
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	ret = mount(NULL, "/", NULL, MS_REC | MS_PRIVATE, 0);
	if (ret < 0) {
		fprintf(stderr, "%s - Failed to mount / as private\n",
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	ret = mkdir("/dev/binderfs", 0755);
	if (ret < 0 && errno != EEXIST) {
		fprintf(stderr, "%s - Failed to create binderfs mountpoint\n",
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	ret = mount(NULL, "/dev/binderfs", "binder", 0, 0);
	if (ret < 0) {
		fprintf(stderr, "%s - Failed to mount binderfs\n",
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	memcpy(device.name, "my-binder", strlen("my-binder"));

	fd = open("/dev/binderfs/binder-control", O_RDONLY | O_CLOEXEC);
	if (fd < 0) {
		fprintf(stderr, "%s - Failed to open binder-control device\n",
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	ret = ioctl(fd, BINDER_CTL_ADD, &device);
	saved_errno = errno;
	close(fd);
	errno = saved_errno;
	if (ret < 0) {
		fprintf(stderr, "%s - Failed to allocate new binder device\n",
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("Allocated new binder device with major %d, minor %d, and name %s\n",
	       device.major, device.minor, device.name);

	ret = unlink("/dev/binderfs/my-binder");
	if (ret < 0) {
		fprintf(stderr, "%s - Failed to delete binder device\n",
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Cleanup happens when the mount namespace dies. */
	exit(EXIT_SUCCESS);
}