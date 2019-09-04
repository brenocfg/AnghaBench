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
typedef  int u16 ;
struct r8a66597 {int dummy; } ;

/* Variables and functions */
 int ATTCHE ; 
 int BURST ; 
 int CPU_ADR_RD_WR ; 
 int DCFM ; 
 int DRPD ; 
 int /*<<< orphan*/  DTCHE ; 
 int HSE ; 
 int /*<<< orphan*/  get_dmacfg_reg (int) ; 
 int /*<<< orphan*/  get_intenb_reg (int) ; 
 int /*<<< orphan*/  get_syscfg_reg (int) ; 
 int /*<<< orphan*/  r8a66597_bclr (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_bset (struct r8a66597*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_write (struct r8a66597*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r8a66597_enable_port(struct r8a66597 *r8a66597, int port)
{
	u16 val;

	val = port ? DRPD : DCFM | DRPD;
	r8a66597_bset(r8a66597, val, get_syscfg_reg(port));
	r8a66597_bset(r8a66597, HSE, get_syscfg_reg(port));

	r8a66597_write(r8a66597, BURST | CPU_ADR_RD_WR, get_dmacfg_reg(port));
	r8a66597_bclr(r8a66597, DTCHE, get_intenb_reg(port));
	r8a66597_bset(r8a66597, ATTCHE, get_intenb_reg(port));
}