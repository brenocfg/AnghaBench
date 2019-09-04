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
struct mtk_eth {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7621_RESET_FE ; 
 int /*<<< orphan*/  mtk_reset (struct mtk_eth*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt7621_mtk_reset(struct mtk_eth *eth)
{
	mtk_reset(eth, MT7621_RESET_FE);
}