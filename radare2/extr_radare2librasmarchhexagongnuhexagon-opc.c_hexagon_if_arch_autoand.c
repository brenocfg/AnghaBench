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
 scalar_t__ hexagon_if_arch_v4 () ; 
 scalar_t__ hexagon_if_arch_v5 () ; 

int
hexagon_if_arch_autoand
(void)
{
  return (hexagon_if_arch_v4 () || hexagon_if_arch_v5 ());
}