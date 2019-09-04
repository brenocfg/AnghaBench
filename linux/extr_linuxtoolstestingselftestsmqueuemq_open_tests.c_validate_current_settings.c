#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int rlim_cur; int rlim_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_MSGQUEUE ; 
 int cur_def_msgs ; 
 int cur_def_msgsize ; 
 TYPE_1__ cur_limits ; 
 int cur_max_msgs ; 
 int cur_max_msgsize ; 
 int /*<<< orphan*/  def_msgs ; 
 int /*<<< orphan*/  def_msgsize ; 
 scalar_t__ default_settings ; 
 int /*<<< orphan*/  max_msgs ; 
 int /*<<< orphan*/  max_msgsize ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setr (int /*<<< orphan*/ ,TYPE_1__*) ; 

void validate_current_settings()
{
	int rlim_needed;

	if (cur_limits.rlim_cur < 4096) {
		printf("Current rlimit value for POSIX message queue bytes is "
		       "unreasonably low,\nincreasing.\n\n");
		cur_limits.rlim_cur = 8192;
		cur_limits.rlim_max = 16384;
		setr(RLIMIT_MSGQUEUE, &cur_limits);
	}

	if (default_settings) {
		rlim_needed = (cur_def_msgs + 1) * (cur_def_msgsize + 1 +
						    2 * sizeof(void *));
		if (rlim_needed > cur_limits.rlim_cur) {
			printf("Temporarily lowering default queue parameters "
			       "to something that will work\n"
			       "with the current rlimit values.\n\n");
			set(def_msgs, 10);
			cur_def_msgs = 10;
			set(def_msgsize, 128);
			cur_def_msgsize = 128;
		}
	} else {
		rlim_needed = (cur_max_msgs + 1) * (cur_max_msgsize + 1 +
						    2 * sizeof(void *));
		if (rlim_needed > cur_limits.rlim_cur) {
			printf("Temporarily lowering maximum queue parameters "
			       "to something that will work\n"
			       "with the current rlimit values in case this is "
			       "a kernel that ties the default\n"
			       "queue parameters to the maximum queue "
			       "parameters.\n\n");
			set(max_msgs, 10);
			cur_max_msgs = 10;
			set(max_msgsize, 128);
			cur_max_msgsize = 128;
		}
	}
}