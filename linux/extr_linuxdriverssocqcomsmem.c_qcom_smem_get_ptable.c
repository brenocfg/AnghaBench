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
typedef  int u32 ;
struct smem_ptable {int /*<<< orphan*/  version; int /*<<< orphan*/  magic; } ;
struct qcom_smem {int /*<<< orphan*/  dev; TYPE_1__* regions; } ;
struct TYPE_2__ {int size; int /*<<< orphan*/  virt_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 struct smem_ptable* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMEM_PTABLE_MAGIC ; 
 int /*<<< orphan*/  SZ_4K ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct smem_ptable *qcom_smem_get_ptable(struct qcom_smem *smem)
{
	struct smem_ptable *ptable;
	u32 version;

	ptable = smem->regions[0].virt_base + smem->regions[0].size - SZ_4K;
	if (memcmp(ptable->magic, SMEM_PTABLE_MAGIC, sizeof(ptable->magic)))
		return ERR_PTR(-ENOENT);

	version = le32_to_cpu(ptable->version);
	if (version != 1) {
		dev_err(smem->dev,
			"Unsupported partition header version %d\n", version);
		return ERR_PTR(-EINVAL);
	}
	return ptable;
}