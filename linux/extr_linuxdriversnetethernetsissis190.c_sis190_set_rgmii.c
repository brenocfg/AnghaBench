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
typedef  int u8 ;
struct sis190_private {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_HAS_RGMII ; 

__attribute__((used)) static void sis190_set_rgmii(struct sis190_private *tp, u8 reg)
{
	tp->features |= (reg & 0x80) ? F_HAS_RGMII : 0;
}