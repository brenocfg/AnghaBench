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
struct input_handle {struct bh_priv* private; } ;
struct bh_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_close_device (struct input_handle*) ; 
 int /*<<< orphan*/  input_unregister_handle (struct input_handle*) ; 
 int /*<<< orphan*/  kfree (struct bh_priv*) ; 

__attribute__((used)) static void button_hotplug_disconnect(struct input_handle *handle)
{
	struct bh_priv *priv = handle->private;

	input_close_device(handle);
	input_unregister_handle(handle);

	kfree(priv);
}