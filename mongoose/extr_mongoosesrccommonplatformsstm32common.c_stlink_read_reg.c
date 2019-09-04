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
struct stlink_reg {int dummy; } ;
typedef  int /*<<< orphan*/  stlink_t ;

/* Variables and functions */
 int _stlink_usb_read_reg (int /*<<< orphan*/ *,int,struct stlink_reg*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

int stlink_read_reg(stlink_t *sl, int r_idx, struct stlink_reg *regp) {
  if (r_idx > 20 || r_idx < 0) {
    fprintf(stderr, "Error: register index must be in [0..20]\n");
    return -1;
  }

  return _stlink_usb_read_reg(sl, r_idx, regp);
}