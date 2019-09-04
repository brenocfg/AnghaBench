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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SAVED_CMDLINES_DEFAULT ; 
 int allocate_cmdlines_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * savedcmd ; 

__attribute__((used)) static int trace_create_savedcmd(void)
{
	int ret;

	savedcmd = kmalloc(sizeof(*savedcmd), GFP_KERNEL);
	if (!savedcmd)
		return -ENOMEM;

	ret = allocate_cmdlines_buffer(SAVED_CMDLINES_DEFAULT, savedcmd);
	if (ret < 0) {
		kfree(savedcmd);
		savedcmd = NULL;
		return -ENOMEM;
	}

	return 0;
}