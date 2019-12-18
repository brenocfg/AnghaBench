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
 int /*<<< orphan*/  NAS ; 
 int /*<<< orphan*/  NAS_NUMLOCK ; 
 int /*<<< orphan*/  NAS_TENKEY ; 
 int /*<<< orphan*/  NAS_TENKEY_NUMLOCK ; 
 int /*<<< orphan*/  layer_set (int,int /*<<< orphan*/ ) ; 
 scalar_t__ numlock_enabled ; 
 scalar_t__ tenkey_enabled ; 

__attribute__((used)) static void set_nas(bool on) {
  /* Always turn on the base NAS layer so other layers can fall through. */
  layer_set(on, NAS);

  layer_set(on && numlock_enabled, NAS_NUMLOCK);
  layer_set(on && tenkey_enabled, NAS_TENKEY);
  layer_set(on && tenkey_enabled && numlock_enabled, NAS_TENKEY_NUMLOCK);
}