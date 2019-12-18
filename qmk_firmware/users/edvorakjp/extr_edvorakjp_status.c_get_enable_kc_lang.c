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
struct TYPE_2__ {int enable_kc_lang; } ;

/* Variables and functions */
 TYPE_1__ edvorakjp_config ; 

bool get_enable_kc_lang(void) {
  return edvorakjp_config.enable_kc_lang;
}