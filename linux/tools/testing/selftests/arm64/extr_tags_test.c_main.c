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
struct utsname {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PR_SET_TAGGED_ADDR_CTRL ; 
 int /*<<< orphan*/  PR_TAGGED_ADDR_ENABLE ; 
 scalar_t__ SET_TAG (struct utsname*,unsigned long) ; 
 int /*<<< orphan*/  free (struct utsname*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ prctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uname (struct utsname*) ; 

int main(void)
{
	static int tbi_enabled = 0;
	unsigned long tag = 0;
	struct utsname *ptr;
	int err;

	if (prctl(PR_SET_TAGGED_ADDR_CTRL, PR_TAGGED_ADDR_ENABLE, 0, 0, 0) == 0)
		tbi_enabled = 1;
	ptr = (struct utsname *)malloc(sizeof(*ptr));
	if (tbi_enabled)
		tag = 0x42;
	ptr = (struct utsname *)SET_TAG(ptr, tag);
	err = uname(ptr);
	free(ptr);

	return err;
}