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
struct TYPE_2__ {void* stdout; int /*<<< orphan*/  log_cnt; int /*<<< orphan*/  log_buf; scalar_t__ verbose; void* stderr; } ;

/* Variables and functions */
 TYPE_1__ env ; 
 int /*<<< orphan*/  fflush (void*) ; 
 void* open_memstream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 void* stderr ; 
 void* stdout ; 

__attribute__((used)) static void stdio_hijack(void)
{
#ifdef __GLIBC__
	env.stdout = stdout;
	env.stderr = stderr;

	if (env.verbose) {
		/* nothing to do, output to stdout by default */
		return;
	}

	/* stdout and stderr -> buffer */
	fflush(stdout);

	stdout = open_memstream(&env.log_buf, &env.log_cnt);
	if (!stdout) {
		stdout = env.stdout;
		perror("open_memstream");
		return;
	}

	stderr = stdout;
#endif
}