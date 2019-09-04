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
typedef  int /*<<< orphan*/  u32 ;
struct smem_ptable {size_t num_entries; int /*<<< orphan*/ * entry; } ;
struct smem_info {int /*<<< orphan*/  num_items; int /*<<< orphan*/  magic; } ;
struct qcom_smem {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct smem_ptable*) ; 
 int /*<<< orphan*/  SMEM_INFO_MAGIC ; 
 int /*<<< orphan*/  SMEM_ITEM_COUNT ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct smem_ptable* qcom_smem_get_ptable (struct qcom_smem*) ; 

__attribute__((used)) static u32 qcom_smem_get_item_count(struct qcom_smem *smem)
{
	struct smem_ptable *ptable;
	struct smem_info *info;

	ptable = qcom_smem_get_ptable(smem);
	if (IS_ERR_OR_NULL(ptable))
		return SMEM_ITEM_COUNT;

	info = (struct smem_info *)&ptable->entry[ptable->num_entries];
	if (memcmp(info->magic, SMEM_INFO_MAGIC, sizeof(info->magic)))
		return SMEM_ITEM_COUNT;

	return le16_to_cpu(info->num_items);
}