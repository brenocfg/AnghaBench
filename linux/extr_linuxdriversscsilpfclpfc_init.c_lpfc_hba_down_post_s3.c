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
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_hba_clean_txcmplq (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_hba_free_post_buf (struct lpfc_hba*) ; 

__attribute__((used)) static int
lpfc_hba_down_post_s3(struct lpfc_hba *phba)
{
	lpfc_hba_free_post_buf(phba);
	lpfc_hba_clean_txcmplq(phba);
	return 0;
}