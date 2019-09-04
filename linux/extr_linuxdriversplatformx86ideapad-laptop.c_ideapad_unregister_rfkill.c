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
struct ideapad_private {int /*<<< orphan*/ * rfk; } ;

/* Variables and functions */
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ideapad_unregister_rfkill(struct ideapad_private *priv, int dev)
{
	if (!priv->rfk[dev])
		return;

	rfkill_unregister(priv->rfk[dev]);
	rfkill_destroy(priv->rfk[dev]);
}