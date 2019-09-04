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
struct mtk_hsdam_engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_hsdma_rx (struct mtk_hsdam_engine*) ; 
 int /*<<< orphan*/  mtk_hsdma_tx (struct mtk_hsdam_engine*) ; 

__attribute__((used)) static void mtk_hsdma_tasklet(unsigned long arg)
{
	struct mtk_hsdam_engine *hsdma = (struct mtk_hsdam_engine *)arg;

	mtk_hsdma_rx(hsdma);
	mtk_hsdma_tx(hsdma);
}