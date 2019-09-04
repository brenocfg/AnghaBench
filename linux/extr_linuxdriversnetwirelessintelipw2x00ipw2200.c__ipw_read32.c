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
struct ipw_priv {scalar_t__ hw_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline u32 _ipw_read32(struct ipw_priv *ipw, unsigned long ofs)
{
	return readl(ipw->hw_base + ofs);
}