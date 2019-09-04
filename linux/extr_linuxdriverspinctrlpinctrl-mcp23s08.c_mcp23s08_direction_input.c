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
struct mcp23s08 {int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCP_IODIR ; 
 struct mcp23s08* gpiochip_get_data (struct gpio_chip*) ; 
 int mcp_set_bit (struct mcp23s08*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mcp23s08_direction_input(struct gpio_chip *chip, unsigned offset)
{
	struct mcp23s08	*mcp = gpiochip_get_data(chip);
	int status;

	mutex_lock(&mcp->lock);
	status = mcp_set_bit(mcp, MCP_IODIR, offset, true);
	mutex_unlock(&mcp->lock);

	return status;
}