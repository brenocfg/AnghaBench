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
struct mcp23s08 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCP_OLAT ; 
 int mcp_set_mask (struct mcp23s08*,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int __mcp23s08_set(struct mcp23s08 *mcp, unsigned mask, bool value)
{
	return mcp_set_mask(mcp, MCP_OLAT, mask, value);
}