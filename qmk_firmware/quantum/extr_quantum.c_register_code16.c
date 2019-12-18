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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ IS_MOD (scalar_t__) ; 
 scalar_t__ KC_NO ; 
 int /*<<< orphan*/  do_code16 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (scalar_t__) ; 
 int /*<<< orphan*/  register_mods ; 
 int /*<<< orphan*/  register_weak_mods ; 

void register_code16(uint16_t code) {
    if (IS_MOD(code) || code == KC_NO) {
        do_code16(code, register_mods);
    } else {
        do_code16(code, register_weak_mods);
    }
    register_code(code);
}