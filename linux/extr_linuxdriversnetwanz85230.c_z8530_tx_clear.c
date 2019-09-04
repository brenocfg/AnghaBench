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
struct z8530_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RES_H_IUS ; 
 int /*<<< orphan*/  RES_Tx_P ; 
 int /*<<< orphan*/  write_zsctrl (struct z8530_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void z8530_tx_clear(struct z8530_channel *c)
{
	write_zsctrl(c, RES_Tx_P);
	write_zsctrl(c, RES_H_IUS);
}