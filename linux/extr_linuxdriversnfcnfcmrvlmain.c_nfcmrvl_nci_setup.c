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
struct nci_dev {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  NFCMRVL_PB_BAIL_OUT ; 
 int /*<<< orphan*/  nci_set_config (struct nci_dev*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int nfcmrvl_nci_setup(struct nci_dev *ndev)
{
	__u8 val = 1;

	nci_set_config(ndev, NFCMRVL_PB_BAIL_OUT, 1, &val);
	return 0;
}