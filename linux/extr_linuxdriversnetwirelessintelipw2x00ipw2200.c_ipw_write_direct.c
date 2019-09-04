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
struct ipw_priv {scalar_t__ hw_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_toio (scalar_t__,void*,int) ; 

__attribute__((used)) static void ipw_write_direct(struct ipw_priv *priv, u32 addr, void *buf,
			     int num)
{
	memcpy_toio((priv->hw_base + addr), buf, num);
}