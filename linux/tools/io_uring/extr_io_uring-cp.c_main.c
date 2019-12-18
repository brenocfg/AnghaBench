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
struct io_uring {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  QD ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int copy_file (struct io_uring*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_file_size (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ infd ; 
 int /*<<< orphan*/  io_uring_queue_exit (struct io_uring*) ; 
 scalar_t__ open (char*,int,...) ; 
 scalar_t__ outfd ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ setup_context (int /*<<< orphan*/ ,struct io_uring*) ; 

int main(int argc, char *argv[])
{
	struct io_uring ring;
	off_t insize;
	int ret;

	if (argc < 3) {
		printf("%s: infile outfile\n", argv[0]);
		return 1;
	}

	infd = open(argv[1], O_RDONLY);
	if (infd < 0) {
		perror("open infile");
		return 1;
	}
	outfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfd < 0) {
		perror("open outfile");
		return 1;
	}

	if (setup_context(QD, &ring))
		return 1;
	if (get_file_size(infd, &insize))
		return 1;

	ret = copy_file(&ring, insize);

	close(infd);
	close(outfd);
	io_uring_queue_exit(&ring);
	return ret;
}