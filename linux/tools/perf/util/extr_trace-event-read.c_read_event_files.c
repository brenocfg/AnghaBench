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
 int /*<<< orphan*/  free (char*) ; 
 int read4 (struct tep_handle*) ; 
 unsigned long long read8 (struct tep_handle*) ; 
 int read_event_file (struct tep_handle*,char*,unsigned long long) ; 
 char* read_string () ; 

__attribute__((used)) static int read_event_files(struct tep_handle *pevent)
{
	unsigned long long size;
	char *sys;
	int systems;
	int count;
	int i,x;
	int ret;

	systems = read4(pevent);

	for (i = 0; i < systems; i++) {
		sys = read_string();
		if (sys == NULL)
			return -1;

		count = read4(pevent);

		for (x=0; x < count; x++) {
			size = read8(pevent);
			ret = read_event_file(pevent, sys, size);
			if (ret) {
				free(sys);
				return ret;
			}
		}
		free(sys);
	}
	return 0;
}