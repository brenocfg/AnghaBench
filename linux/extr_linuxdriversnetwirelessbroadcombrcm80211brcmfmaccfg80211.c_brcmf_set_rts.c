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
 int /*<<< orphan*/  brcmf_err (char*,scalar_t__) ; 
 scalar_t__ brcmf_fil_iovar_int_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 

__attribute__((used)) static s32 brcmf_set_rts(struct net_device *ndev, u32 rts_threshold)
{
	s32 err = 0;

	err = brcmf_fil_iovar_int_set(netdev_priv(ndev), "rtsthresh",
				      rts_threshold);
	if (err)
		brcmf_err("Error (%d)\n", err);

	return err;
}