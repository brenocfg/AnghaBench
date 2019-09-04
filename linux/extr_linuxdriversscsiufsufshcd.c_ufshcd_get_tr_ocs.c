#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ufshcd_lrb {TYPE_2__* utr_descriptor_ptr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dword_2; } ;
struct TYPE_4__ {TYPE_1__ header; } ;

/* Variables and functions */
 int MASK_OCS ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ufshcd_get_tr_ocs(struct ufshcd_lrb *lrbp)
{
	return le32_to_cpu(lrbp->utr_descriptor_ptr->header.dword_2) & MASK_OCS;
}