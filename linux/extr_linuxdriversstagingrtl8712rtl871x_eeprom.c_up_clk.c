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
typedef  int u16 ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_RATE ; 
 int /*<<< orphan*/  EE_9346CR ; 
 int _EESK ; 
 int /*<<< orphan*/  r8712_write8 (struct _adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void up_clk(struct _adapter *padapter, u16 *x)
{
	*x = *x | _EESK;
	r8712_write8(padapter, EE_9346CR, (u8)*x);
	udelay(CLOCK_RATE);
}