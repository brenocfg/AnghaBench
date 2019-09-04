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
struct TYPE_2__ {int /*<<< orphan*/  line; } ;
struct mpsc_port_info {int /*<<< orphan*/  brg_clk_src; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_get_cache_alignment () ; 
 int /*<<< orphan*/  mpsc_brg_enable (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  mpsc_brg_init (struct mpsc_port_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpsc_hw_init (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  mpsc_sdma_init (struct mpsc_port_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpsc_sdma_stop (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpsc_init_hw(struct mpsc_port_info *pi)
{
	pr_debug("mpsc_init_hw[%d]: Initializing\n", pi->port.line);

	mpsc_brg_init(pi, pi->brg_clk_src);
	mpsc_brg_enable(pi);
	mpsc_sdma_init(pi, dma_get_cache_alignment());	/* burst a cacheline */
	mpsc_sdma_stop(pi);
	mpsc_hw_init(pi);
}