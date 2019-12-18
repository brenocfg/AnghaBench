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
typedef  scalar_t__ int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  NORM ; 
 int /*<<< orphan*/  PIXEL_ON ; 
 int /*<<< orphan*/  XOR ; 
 int /*<<< orphan*/  draw_char (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_rect_filled_soft (scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_string (scalar_t__,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ layer ; 

void draw_layer_section(int8_t startX, int8_t startY, bool show_legend){
  if(show_legend){
    draw_string(startX + 1, startY + 2, "LAYER", PIXEL_ON, NORM, 0);
  } else {
    startX -= 32;
  }
  draw_rect_filled_soft(startX + 32, startY + 1, 9, 9, PIXEL_ON, NORM);
  draw_char(startX + 34, startY + 2, layer + 0x30, PIXEL_ON, XOR, 0);
}