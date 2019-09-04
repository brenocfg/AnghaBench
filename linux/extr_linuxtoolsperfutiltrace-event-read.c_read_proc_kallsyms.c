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
struct tep_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  input_fd ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int read4 (struct tep_handle*) ; 
 unsigned int trace_data_size ; 

__attribute__((used)) static int read_proc_kallsyms(struct tep_handle *pevent)
{
	unsigned int size;

	size = read4(pevent);
	if (!size)
		return 0;
	/*
	 * Just skip it, now that we configure libtraceevent to use the
	 * tools/perf/ symbol resolver.
	 *
	 * We need to skip it so that we can continue parsing old perf.data
	 * files, that contains this /proc/kallsyms payload.
	 *
	 * Newer perf.data files will have just the 4-bytes zeros "kallsyms
	 * payload", so that older tools can continue reading it and interpret
	 * it as "no kallsyms payload is present".
	 */
	lseek(input_fd, size, SEEK_CUR);
	trace_data_size += size;
	return 0;
}