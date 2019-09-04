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
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_OP_START_LIMITED_DISCOVERY ; 
 int start_discovery_internal (struct sock*,struct hci_dev*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_limited_discovery(struct sock *sk, struct hci_dev *hdev,
				   void *data, u16 len)
{
	return start_discovery_internal(sk, hdev,
					MGMT_OP_START_LIMITED_DISCOVERY,
					data, len);
}