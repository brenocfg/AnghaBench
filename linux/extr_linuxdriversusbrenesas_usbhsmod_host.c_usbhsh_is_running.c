#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * irq_attch; } ;
struct usbhsh_hpriv {TYPE_1__ mod; } ;

/* Variables and functions */

__attribute__((used)) static int usbhsh_is_running(struct usbhsh_hpriv *hpriv)
{
	/*
	 * we can decide some device is attached or not
	 * by checking mod.irq_attch
	 * see
	 *	usbhsh_irq_attch()
	 *	usbhsh_irq_dtch()
	 */
	return (hpriv->mod.irq_attch == NULL);
}