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
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_IO (char*,struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPW_INDIRECT_ADDR ; 
 int /*<<< orphan*/  IPW_INDIRECT_DATA ; 
 int /*<<< orphan*/  _ipw_write32 (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _ipw_write_reg32(struct ipw_priv *priv, u32 reg, u32 value)
{
	IPW_DEBUG_IO(" %p : reg = 0x%8X : value = 0x%8X\n", priv, reg, value);
	_ipw_write32(priv, IPW_INDIRECT_ADDR, reg);
	_ipw_write32(priv, IPW_INDIRECT_DATA, value);
}