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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  keyrecord_t ;

/* Variables and functions */
 scalar_t__ process_record_edvorakjp_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ process_record_edvorakjp_swap_scln (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ process_record_ime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ process_record_keymap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ process_record_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_record_keymap(keycode, record) &&\
         process_record_edvorakjp_swap_scln(keycode, record) &&\
         process_record_edvorakjp_config(keycode, record) &&\
         process_record_layer(keycode, record) &&\
         process_record_ime(keycode, record);
}