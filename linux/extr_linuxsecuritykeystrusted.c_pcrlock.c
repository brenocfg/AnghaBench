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
 int SHA1_DIGEST_SIZE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int tpm_get_random (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ tpm_pcr_extend (int /*<<< orphan*/ *,int const,unsigned char*) ; 

__attribute__((used)) static int pcrlock(const int pcrnum)
{
	unsigned char hash[SHA1_DIGEST_SIZE];
	int ret;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	ret = tpm_get_random(NULL, hash, SHA1_DIGEST_SIZE);
	if (ret != SHA1_DIGEST_SIZE)
		return ret;
	return tpm_pcr_extend(NULL, pcrnum, hash) ? -EINVAL : 0;
}