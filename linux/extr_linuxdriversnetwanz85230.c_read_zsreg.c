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
typedef  scalar_t__ u8 ;
struct z8530_channel {int /*<<< orphan*/  ctrlio; } ;

/* Variables and functions */
 scalar_t__ z8530_read_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  z8530_write_port (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline u8 read_zsreg(struct z8530_channel *c, u8 reg)
{
	if(reg)
		z8530_write_port(c->ctrlio, reg);
	return z8530_read_port(c->ctrlio);
}