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

/* Variables and functions */
 int /*<<< orphan*/  dma_debug_initialized ; 
 scalar_t__ global_disable ; 

__attribute__((used)) static inline bool dma_debug_disabled(void)
{
	return global_disable || !dma_debug_initialized;
}