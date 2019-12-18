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
struct perf_pipe_file_header {int /*<<< orphan*/  size; int /*<<< orphan*/  magic; } ;
struct perf_header {scalar_t__ needs_swap; } ;
struct feat_fd {struct perf_header* ph; int /*<<< orphan*/  fd; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  bswap_64 (int /*<<< orphan*/ ) ; 
 scalar_t__ check_magic_endian (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct perf_header*) ; 
 scalar_t__ do_write (struct feat_fd*,struct perf_pipe_file_header*,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ readn (int,struct perf_pipe_file_header*,int) ; 

__attribute__((used)) static int perf_file_header__read_pipe(struct perf_pipe_file_header *header,
				       struct perf_header *ph, int fd,
				       bool repipe)
{
	struct feat_fd ff = {
		.fd = STDOUT_FILENO,
		.ph = ph,
	};
	ssize_t ret;

	ret = readn(fd, header, sizeof(*header));
	if (ret <= 0)
		return -1;

	if (check_magic_endian(header->magic, header->size, true, ph) < 0) {
		pr_debug("endian/magic failed\n");
		return -1;
	}

	if (ph->needs_swap)
		header->size = bswap_64(header->size);

	if (repipe && do_write(&ff, header, sizeof(*header)) < 0)
		return -1;

	return 0;
}