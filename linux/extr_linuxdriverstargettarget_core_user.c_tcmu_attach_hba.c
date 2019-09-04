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
struct tcmu_hba {int /*<<< orphan*/  host_id; } ;
struct se_hba {struct tcmu_hba* hba_ptr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tcmu_hba* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcmu_attach_hba(struct se_hba *hba, u32 host_id)
{
	struct tcmu_hba *tcmu_hba;

	tcmu_hba = kzalloc(sizeof(struct tcmu_hba), GFP_KERNEL);
	if (!tcmu_hba)
		return -ENOMEM;

	tcmu_hba->host_id = host_id;
	hba->hba_ptr = tcmu_hba;

	return 0;
}