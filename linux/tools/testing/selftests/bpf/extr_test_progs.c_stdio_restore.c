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
struct TYPE_2__ {scalar_t__ stdout; int /*<<< orphan*/  stderr; scalar_t__ log_cnt; int /*<<< orphan*/ * log_buf; } ;

/* Variables and functions */
 TYPE_1__ env ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stdout ; 

__attribute__((used)) static void stdio_restore(void)
{
#ifdef __GLIBC__
	if (stdout == env.stdout)
		return;

	fclose(stdout);
	free(env.log_buf);

	env.log_buf = NULL;
	env.log_cnt = 0;

	stdout = env.stdout;
	stderr = env.stderr;
#endif
}