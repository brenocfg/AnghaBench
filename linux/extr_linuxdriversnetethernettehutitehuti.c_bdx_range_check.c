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
typedef  scalar_t__ u32 ;
struct bdx_priv {TYPE_1__* nic; } ;
struct TYPE_2__ {int port_num; } ;

/* Variables and functions */
 int BDX_REGS_SIZE ; 
 int EINVAL ; 

__attribute__((used)) static int bdx_range_check(struct bdx_priv *priv, u32 offset)
{
	return (offset > (u32) (BDX_REGS_SIZE / priv->nic->port_num)) ?
		-EINVAL : 0;
}