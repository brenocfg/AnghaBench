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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_iocbq {int dummy; } ;
struct lpfc_hba {int dummy; } ;
struct lpfc_dmabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_ct_ignore_hbq_buffer (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_dmabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_ct_unsol_buffer(struct lpfc_hba *phba, struct lpfc_iocbq *piocbq,
		     struct lpfc_dmabuf *mp, uint32_t size)
{
	lpfc_ct_ignore_hbq_buffer(phba, piocbq, mp, size);
}