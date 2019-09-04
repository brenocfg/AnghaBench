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
struct aspeed_pin_config {unsigned int* pins; } ;

/* Variables and functions */

__attribute__((used)) static inline bool pin_in_config_range(unsigned int offset,
		const struct aspeed_pin_config *config)
{
	return offset >= config->pins[0] && offset <= config->pins[1];
}