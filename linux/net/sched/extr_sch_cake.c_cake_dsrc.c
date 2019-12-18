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
 int CAKE_FLOW_DUAL_SRC ; 

__attribute__((used)) static bool cake_dsrc(int flow_mode)
{
	return (flow_mode & CAKE_FLOW_DUAL_SRC) == CAKE_FLOW_DUAL_SRC;
}