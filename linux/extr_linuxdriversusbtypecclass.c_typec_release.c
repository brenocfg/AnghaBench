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
struct typec_port {int /*<<< orphan*/  mux; int /*<<< orphan*/  sw; int /*<<< orphan*/  mode_ids; int /*<<< orphan*/  id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct typec_port*) ; 
 struct typec_port* to_typec_port (struct device*) ; 
 int /*<<< orphan*/  typec_index_ida ; 
 int /*<<< orphan*/  typec_mux_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_switch_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void typec_release(struct device *dev)
{
	struct typec_port *port = to_typec_port(dev);

	ida_simple_remove(&typec_index_ida, port->id);
	ida_destroy(&port->mode_ids);
	typec_switch_put(port->sw);
	typec_mux_put(port->mux);
	kfree(port);
}