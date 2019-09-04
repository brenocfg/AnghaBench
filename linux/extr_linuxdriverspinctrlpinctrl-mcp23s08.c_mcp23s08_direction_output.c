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
 unsigned int BIT (unsigned int) ; 
 int /*<<< orphan*/  MCP_IODIR ; 
 int __mcp23s08_set (struct mcp23s08*,unsigned int,int) ; 
 struct mcp23s08* gpiochip_get_data (struct gpio_chip*) ; 
 int mcp_set_mask (struct mcp23s08*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mcp23s08_direction_output(struct gpio_chip *chip, unsigned offset, int value)
{
	struct mcp23s08	*mcp = gpiochip_get_data(chip);
	unsigned mask = BIT(offset);
	int status;

	mutex_lock(&mcp->lock);
	status = __mcp23s08_set(mcp, mask, value);
	if (status == 0) {
		status = mcp_set_mask(mcp, MCP_IODIR, mask, false);
	}
	mutex_unlock(&mcp->lock);
	return status;
}