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
typedef  int /*<<< orphan*/  teken_pos_t ;
typedef  int /*<<< orphan*/  teken_char_t ;
typedef  int /*<<< orphan*/  teken_attr_t ;

/* Variables and functions */

__attribute__((used)) static void dummy_putchar(void *s, const teken_pos_t *p, teken_char_t c,
                          const teken_attr_t *a) {}