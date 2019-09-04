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
 int /*<<< orphan*/  ravb_modify (struct net_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ravb_rcv_snd_disable(struct net_device *ndev)
{
	/* Disable TX and RX */
	ravb_modify(ndev, ECMR, ECMR_RE | ECMR_TE, 0);
}