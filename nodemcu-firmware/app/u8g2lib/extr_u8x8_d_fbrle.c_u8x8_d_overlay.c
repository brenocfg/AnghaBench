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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  u8x8_t ;
struct TYPE_3__ {int (* hardware_display_cb ) (int /*<<< orphan*/ *,int,int,void*) ;} ;
struct TYPE_4__ {TYPE_1__ overlay; } ;
typedef  TYPE_2__ u8g2_nodemcu_t ;

/* Variables and functions */
#define  U8X8_MSG_DISPLAY_SETUP_MEMORY 128 
 int stub1 (int /*<<< orphan*/ *,int,int,void*) ; 
 int stub2 (int /*<<< orphan*/ *,int,int,void*) ; 
 int /*<<< orphan*/  u8x8_d_fbrle (int /*<<< orphan*/ *,int,int,void*) ; 

uint8_t u8x8_d_overlay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  uint8_t res = 1;
  u8g2_nodemcu_t *ext_u8g2 = (u8g2_nodemcu_t *)u8x8;

  switch(msg)
  {
  case U8X8_MSG_DISPLAY_SETUP_MEMORY:
    // only call for hardware display
    if (ext_u8g2->overlay.hardware_display_cb)
      return ext_u8g2->overlay.hardware_display_cb(u8x8, msg, arg_int, arg_ptr);
    break;

  default:
    // forward all messages first to hardware display and then to fbrle
    if (ext_u8g2->overlay.hardware_display_cb)
      res = ext_u8g2->overlay.hardware_display_cb(u8x8, msg, arg_int, arg_ptr);
    u8x8_d_fbrle(u8x8, msg, arg_int, arg_ptr);
    break;
  }

  return res;
}