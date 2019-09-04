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
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_IO (char*,char*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _ipw_write_reg32 (struct ipw_priv*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void ipw_write_reg32(struct ipw_priv *a, u32 b, u32 c)
{
	IPW_DEBUG_IO("%s %d: write_indirect32(0x%08X, 0x%08X)\n", __FILE__,
		     __LINE__, (u32) (b), (u32) (c));
	_ipw_write_reg32(a, b, c);
}