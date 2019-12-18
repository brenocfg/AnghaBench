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
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chip ; 
 int /*<<< orphan*/  digests ; 
 scalar_t__ tpm_pcr_extend (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcrlock(const int pcrnum)
{
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	return tpm_pcr_extend(chip, pcrnum, digests) ? -EINVAL : 0;
}