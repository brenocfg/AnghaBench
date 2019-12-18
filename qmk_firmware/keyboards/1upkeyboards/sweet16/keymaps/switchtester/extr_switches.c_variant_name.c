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
struct mechswitch {size_t variant; } ;

/* Variables and functions */
 char const** VARIANT_NAMES ; 

const char *variant_name(struct mechswitch ms) {
  return VARIANT_NAMES[ms.variant];
}