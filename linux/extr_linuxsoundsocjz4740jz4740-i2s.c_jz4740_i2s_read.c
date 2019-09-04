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
typedef  int /*<<< orphan*/  uint32_t ;
struct jz4740_i2s {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline uint32_t jz4740_i2s_read(const struct jz4740_i2s *i2s,
	unsigned int reg)
{
	return readl(i2s->base + reg);
}