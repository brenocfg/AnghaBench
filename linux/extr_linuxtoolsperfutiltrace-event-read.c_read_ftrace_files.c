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
 int read4 (struct tep_handle*) ; 
 unsigned long long read8 (struct tep_handle*) ; 
 int read_ftrace_file (struct tep_handle*,unsigned long long) ; 

__attribute__((used)) static int read_ftrace_files(struct tep_handle *pevent)
{
	unsigned long long size;
	int count;
	int i;
	int ret;

	count = read4(pevent);

	for (i = 0; i < count; i++) {
		size = read8(pevent);
		ret = read_ftrace_file(pevent, size);
		if (ret)
			return ret;
	}
	return 0;
}