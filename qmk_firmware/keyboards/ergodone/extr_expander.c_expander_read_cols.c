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
 int /*<<< orphan*/  EXPANDER_REG_GPIOA ; 
 int /*<<< orphan*/  expander_input ; 
 int /*<<< orphan*/  expander_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void expander_read_cols(void)
{
  expander_read(EXPANDER_REG_GPIOA, &expander_input);
}