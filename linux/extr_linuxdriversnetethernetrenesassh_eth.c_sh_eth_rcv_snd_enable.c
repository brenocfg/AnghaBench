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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECMR ; 
 int ECMR_RE ; 
 int ECMR_TE ; 
 int /*<<< orphan*/  sh_eth_modify (struct net_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void sh_eth_rcv_snd_enable(struct net_device *ndev)
{
	/* enable tx and rx */
	sh_eth_modify(ndev, ECMR, ECMR_RE | ECMR_TE, ECMR_RE | ECMR_TE);
}