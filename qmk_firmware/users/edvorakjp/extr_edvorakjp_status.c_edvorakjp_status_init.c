#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct TYPE_3__ {int japanese_mode; } ;

/* Variables and functions */
 TYPE_2__ edvorakjp_config ; 
 TYPE_1__ edvorakjp_state ; 
 int /*<<< orphan*/  eeconfig_read_edvorakjp () ; 

void edvorakjp_status_init(void) {
  edvorakjp_state.japanese_mode = false;
  edvorakjp_config.raw = eeconfig_read_edvorakjp();
}