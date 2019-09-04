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
struct ufs_hba {int ufs_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERRUPT_MASK_ALL_VER_10 ; 
 int /*<<< orphan*/  INTERRUPT_MASK_ALL_VER_11 ; 
 int /*<<< orphan*/  INTERRUPT_MASK_ALL_VER_21 ; 
#define  UFSHCI_VERSION_10 131 
#define  UFSHCI_VERSION_11 130 
#define  UFSHCI_VERSION_20 129 
#define  UFSHCI_VERSION_21 128 

__attribute__((used)) static inline u32 ufshcd_get_intr_mask(struct ufs_hba *hba)
{
	u32 intr_mask = 0;

	switch (hba->ufs_version) {
	case UFSHCI_VERSION_10:
		intr_mask = INTERRUPT_MASK_ALL_VER_10;
		break;
	case UFSHCI_VERSION_11:
	case UFSHCI_VERSION_20:
		intr_mask = INTERRUPT_MASK_ALL_VER_11;
		break;
	case UFSHCI_VERSION_21:
	default:
		intr_mask = INTERRUPT_MASK_ALL_VER_21;
		break;
	}

	return intr_mask;
}