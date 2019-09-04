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
typedef  int /*<<< orphan*/  vstr_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 scalar_t__ vstr_add_len (int /*<<< orphan*/ *,int) ; 

void vstr_add_byte(vstr_t *vstr, byte b) {
    byte *buf = (byte*)vstr_add_len(vstr, 1);
    buf[0] = b;
}