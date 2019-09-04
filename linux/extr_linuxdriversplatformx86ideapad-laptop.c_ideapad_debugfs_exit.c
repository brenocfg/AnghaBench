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
struct ideapad_private {int /*<<< orphan*/ * debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ideapad_debugfs_exit(struct ideapad_private *priv)
{
	debugfs_remove_recursive(priv->debug);
	priv->debug = NULL;
}