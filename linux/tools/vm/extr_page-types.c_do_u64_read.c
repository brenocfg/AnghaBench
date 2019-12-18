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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int ULONG_MAX ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,long) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 long pread (int,int /*<<< orphan*/ *,unsigned long,int) ; 

__attribute__((used)) static unsigned long do_u64_read(int fd, const char *name,
				 uint64_t *buf,
				 unsigned long index,
				 unsigned long count)
{
	long bytes;

	if (index > ULONG_MAX / 8)
		fatal("index overflow: %lu\n", index);

	bytes = pread(fd, buf, count * 8, (off_t)index * 8);
	if (bytes < 0) {
		perror(name);
		exit(EXIT_FAILURE);
	}
	if (bytes % 8)
		fatal("partial read: %lu bytes\n", bytes);

	return bytes / 8;
}