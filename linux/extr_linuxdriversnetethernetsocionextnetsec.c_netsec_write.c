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
typedef  scalar_t__ u32 ;
struct netsec_priv {scalar_t__ ioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void netsec_write(struct netsec_priv *priv, u32 reg_addr, u32 val)
{
	writel(val, priv->ioaddr + reg_addr);
}