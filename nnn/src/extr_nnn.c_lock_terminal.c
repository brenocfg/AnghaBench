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
 size_t CMATRIX ; 
 int /*<<< orphan*/  F_NORMAL ; 
 size_t LOCKER ; 
 int /*<<< orphan*/  getutil (char*) ; 
 int /*<<< orphan*/  spawn (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char** utils ; 

__attribute__((used)) static void lock_terminal(void)
{
	char *tmp = utils[LOCKER];

	if (!getutil(tmp))
		tmp = utils[CMATRIX];

	spawn(tmp, NULL, NULL, NULL, F_NORMAL);
}