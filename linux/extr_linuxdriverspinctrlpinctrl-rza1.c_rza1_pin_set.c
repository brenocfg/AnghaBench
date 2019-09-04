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
struct rza1_port {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RZA1_P_REG ; 
 int /*<<< orphan*/  rza1_set_bit (struct rza1_port*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void rza1_pin_set(struct rza1_port *port, unsigned int pin,
				unsigned int value)
{
	unsigned long irqflags;

	spin_lock_irqsave(&port->lock, irqflags);
	rza1_set_bit(port, RZA1_P_REG, pin, !!value);
	spin_unlock_irqrestore(&port->lock, irqflags);
}