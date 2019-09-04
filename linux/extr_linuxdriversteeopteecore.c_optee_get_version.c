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
struct tee_ioctl_version_data {int /*<<< orphan*/  gen_caps; int /*<<< orphan*/  impl_caps; int /*<<< orphan*/  impl_id; } ;
struct tee_device {int dummy; } ;
struct optee {int sec_caps; } ;

/* Variables and functions */
 int OPTEE_SMC_SEC_CAP_DYNAMIC_SHM ; 
 int /*<<< orphan*/  TEE_GEN_CAP_GP ; 
 int /*<<< orphan*/  TEE_GEN_CAP_REG_MEM ; 
 int /*<<< orphan*/  TEE_IMPL_ID_OPTEE ; 
 int /*<<< orphan*/  TEE_OPTEE_CAP_TZ ; 
 struct optee* tee_get_drvdata (struct tee_device*) ; 

__attribute__((used)) static void optee_get_version(struct tee_device *teedev,
			      struct tee_ioctl_version_data *vers)
{
	struct tee_ioctl_version_data v = {
		.impl_id = TEE_IMPL_ID_OPTEE,
		.impl_caps = TEE_OPTEE_CAP_TZ,
		.gen_caps = TEE_GEN_CAP_GP,
	};
	struct optee *optee = tee_get_drvdata(teedev);

	if (optee->sec_caps & OPTEE_SMC_SEC_CAP_DYNAMIC_SHM)
		v.gen_caps |= TEE_GEN_CAP_REG_MEM;
	*vers = v;
}