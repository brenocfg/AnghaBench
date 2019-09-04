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
struct mtk_rtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_r32 (struct mtk_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_rmw(struct mtk_rtc *rtc, u32 reg, u32 mask, u32 set)
{
	u32 val;

	val = mtk_r32(rtc, reg);
	val &= ~mask;
	val |= set;
	mtk_w32(rtc, reg, val);
}