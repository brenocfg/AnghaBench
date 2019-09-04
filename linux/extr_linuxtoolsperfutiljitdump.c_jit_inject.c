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
struct jit_buf_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  jit_close (struct jit_buf_desc*) ; 
 int jit_open (struct jit_buf_desc*,char*) ; 
 int jit_process_dump (struct jit_buf_desc*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int
jit_inject(struct jit_buf_desc *jd, char *path)
{
	int ret;

	if (verbose > 0)
		fprintf(stderr, "injecting: %s\n", path);

	ret = jit_open(jd, path);
	if (ret)
		return -1;

	ret = jit_process_dump(jd);

	jit_close(jd);

	if (verbose > 0)
		fprintf(stderr, "injected: %s (%d)\n", path, ret);

	return 0;
}