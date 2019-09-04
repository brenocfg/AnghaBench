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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  type ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_OP_PROP_PATCH_OID ; 
 int nci_prop_cmd (struct nci_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int fdp_nci_patch_cmd(struct nci_dev *ndev, u8 type)
{
	return nci_prop_cmd(ndev, NCI_OP_PROP_PATCH_OID, sizeof(type), &type);
}