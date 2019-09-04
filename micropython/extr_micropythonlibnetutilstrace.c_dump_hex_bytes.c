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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  mp_print_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_printf (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void dump_hex_bytes(const mp_print_t *print, size_t len, const uint8_t *buf) {
    for (size_t i = 0; i < len; ++i) {
        mp_printf(print, " %02x", buf[i]);
    }
}