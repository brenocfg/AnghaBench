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
struct nci_dev {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_rfprotocol ) (struct nci_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __u32 nci_get_prop_rf_protocol(struct nci_dev *ndev, __u8 rf_protocol)
{
	if (ndev->ops->get_rfprotocol)
		return ndev->ops->get_rfprotocol(ndev, rf_protocol);
	return 0;
}