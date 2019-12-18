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
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GET_PERI_REG_BITS (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CNTL_SLP_WAKEUP ; 
 int /*<<< orphan*/  RTC_STATE0 ; 
 int RTC_STATE1 ; 

int _X_get_rst_cause(void) {
  int ret;
  int a = GET_PERI_REG_BITS(RTC_STATE1, 6, 0);
  if (a == 5) {
    int b = (RTC_STATE1 >> 12) && 0xfff;
    if (b != 1) {
      ret = (b == 8 ? a : 0);
    } else {
      ret = 20;
    }
  } else {
    ret = a;
  }
  CLEAR_PERI_REG_MASK(RTC_STATE0, RTC_CNTL_SLP_WAKEUP);
  return ret;
}