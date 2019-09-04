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
struct net_device {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_C_SET_LRL ; 
 int /*<<< orphan*/  BRCMF_C_SET_SRL ; 
 int /*<<< orphan*/  brcmf_err (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ brcmf_fil_cmd_int_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 

__attribute__((used)) static s32 brcmf_set_retry(struct net_device *ndev, u32 retry, bool l)
{
	s32 err = 0;
	u32 cmd = (l ? BRCMF_C_SET_LRL : BRCMF_C_SET_SRL);

	err = brcmf_fil_cmd_int_set(netdev_priv(ndev), cmd, retry);
	if (err) {
		brcmf_err("cmd (%d) , error (%d)\n", cmd, err);
		return err;
	}
	return err;
}