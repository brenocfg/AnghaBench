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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLMFS_CAPABILITIES ; 
 int strlcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int param_get_dlmfs_capabilities(char *buffer,
					const struct kernel_param *kp)
{
	return strlcpy(buffer, DLMFS_CAPABILITIES,
		       strlen(DLMFS_CAPABILITIES) + 1);
}