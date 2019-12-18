#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct prog_test_def {scalar_t__ force_log; } ;
struct TYPE_2__ {scalar_t__ stdout; int log_cnt; char* log_buf; scalar_t__ verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_1__ env ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  fseeko (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stdout ; 

__attribute__((used)) static void dump_test_log(const struct prog_test_def *test, bool failed)
{
	if (stdout == env.stdout)
		return;

	fflush(stdout); /* exports env.log_buf & env.log_cnt */

	if (env.verbose || test->force_log || failed) {
		if (env.log_cnt) {
			env.log_buf[env.log_cnt] = '\0';
			fprintf(env.stdout, "%s", env.log_buf);
			if (env.log_buf[env.log_cnt - 1] != '\n')
				fprintf(env.stdout, "\n");
		}
	}

	fseeko(stdout, 0, SEEK_SET); /* rewind */
}