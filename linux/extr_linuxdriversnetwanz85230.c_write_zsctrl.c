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
typedef  int /*<<< orphan*/  u8 ;
struct z8530_channel {int /*<<< orphan*/  ctrlio; } ;

/* Variables and functions */
 int /*<<< orphan*/  z8530_write_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void write_zsctrl(struct z8530_channel *c, u8 val)
{
	z8530_write_port(c->ctrlio, val);
}