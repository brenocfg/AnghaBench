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
struct uffdio_api {scalar_t__ api; int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETFD ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  UFFDIO_API ; 
 scalar_t__ UFFD_API ; 
 int /*<<< orphan*/  __NR_userfaultfd ; 
 int /*<<< orphan*/  fcntl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ioctl (scalar_t__,int /*<<< orphan*/ ,struct uffdio_api*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,int) ; 
 scalar_t__ uffd ; 
 int /*<<< orphan*/  uffd_flags ; 

__attribute__((used)) static int userfaultfd_open(int features)
{
	struct uffdio_api uffdio_api;

	uffd = syscall(__NR_userfaultfd, O_CLOEXEC | O_NONBLOCK);
	if (uffd < 0) {
		fprintf(stderr,
			"userfaultfd syscall not available in this kernel\n");
		return 1;
	}
	uffd_flags = fcntl(uffd, F_GETFD, NULL);

	uffdio_api.api = UFFD_API;
	uffdio_api.features = features;
	if (ioctl(uffd, UFFDIO_API, &uffdio_api)) {
		fprintf(stderr, "UFFDIO_API\n");
		return 1;
	}
	if (uffdio_api.api != UFFD_API) {
		fprintf(stderr, "UFFDIO_API error %Lu\n", uffdio_api.api);
		return 1;
	}

	return 0;
}