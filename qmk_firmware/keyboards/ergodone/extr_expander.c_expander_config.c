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
 int /*<<< orphan*/  EXPANDER_REG_GPPUA ; 
 int /*<<< orphan*/  EXPANDER_REG_IODIRB ; 
 int /*<<< orphan*/  EXPANDER_REG_IPOLA ; 
 int /*<<< orphan*/  expander_write (int /*<<< orphan*/ ,int) ; 

void expander_config(void)
{
  expander_write(EXPANDER_REG_IPOLA, 0xFF);
  expander_write(EXPANDER_REG_GPPUA, 0xFF);
  expander_write(EXPANDER_REG_IODIRB, 0xFF);
}