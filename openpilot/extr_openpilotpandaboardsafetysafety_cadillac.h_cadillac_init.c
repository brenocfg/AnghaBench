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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 scalar_t__ cadillac_ign ; 
 scalar_t__ controls_allowed ; 

__attribute__((used)) static void cadillac_init(int16_t param) {
  controls_allowed = 0;
  cadillac_ign = 0;
  #ifdef PANDA
    lline_relay_release();
  #endif
}