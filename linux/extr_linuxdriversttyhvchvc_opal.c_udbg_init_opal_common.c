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
 int /*<<< orphan*/  udbg_getc ; 
 int /*<<< orphan*/  udbg_getc_poll ; 
 int /*<<< orphan*/  udbg_opal_getc ; 
 int /*<<< orphan*/  udbg_opal_getc_poll ; 
 int /*<<< orphan*/  udbg_opal_putc ; 
 int /*<<< orphan*/  udbg_putc ; 

__attribute__((used)) static void udbg_init_opal_common(void)
{
	udbg_putc = udbg_opal_putc;
	udbg_getc = udbg_opal_getc;
	udbg_getc_poll = udbg_opal_getc_poll;
}