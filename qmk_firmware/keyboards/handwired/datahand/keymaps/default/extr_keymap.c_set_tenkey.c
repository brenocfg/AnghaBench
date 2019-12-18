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
 int /*<<< orphan*/  set_nas (int) ; 
 int tenkey_enabled ; 

__attribute__((used)) static void set_tenkey(bool on) {
  tenkey_enabled = on;
  
  /* We have to be on the NAS layer in order to be able to toggle TK.
   * Re-toggle it on so that we move to the right layer (and set the right LED).
   */
  set_nas(true);
}