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
struct mechswitch {int brand; } ;

/* Variables and functions */
 char const** BRAND_NAMES ; 

const char *brand_name(struct mechswitch ms) {
  return BRAND_NAMES[ms.brand - 1];
}