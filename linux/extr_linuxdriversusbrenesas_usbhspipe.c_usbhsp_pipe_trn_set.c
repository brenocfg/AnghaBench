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
typedef  int /*<<< orphan*/  u16 ;
struct usbhs_priv {int dummy; } ;
struct usbhs_pipe {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIPE1TRN ; 
 int /*<<< orphan*/  PIPE2TRN ; 
 int /*<<< orphan*/  PIPE3TRN ; 
 int /*<<< orphan*/  PIPE4TRN ; 
 int /*<<< orphan*/  PIPE5TRN ; 
 int /*<<< orphan*/  PIPE9TRN ; 
 int /*<<< orphan*/  PIPEATRN ; 
 int /*<<< orphan*/  PIPEBTRN ; 
 int /*<<< orphan*/  PIPECTRN ; 
 int /*<<< orphan*/  PIPEDTRN ; 
 int /*<<< orphan*/  PIPEETRN ; 
 int /*<<< orphan*/  PIPEFTRN ; 
 int /*<<< orphan*/  __usbhsp_pipe_xxx_set (struct usbhs_pipe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int usbhs_pipe_number (struct usbhs_pipe*) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 

__attribute__((used)) static void usbhsp_pipe_trn_set(struct usbhs_pipe *pipe, u16 mask, u16 val)
{
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	struct device *dev = usbhs_priv_to_dev(priv);
	int num = usbhs_pipe_number(pipe);
	u16 reg;

	/*
	 * It is impossible to calculate address,
	 * since PIPEnTRN addresses were mapped randomly.
	 */
#define CASE_PIPExTRN(a)		\
	case 0x ## a:			\
		reg = PIPE ## a ## TRN;	\
		break;

	switch (num) {
	CASE_PIPExTRN(1);
	CASE_PIPExTRN(2);
	CASE_PIPExTRN(3);
	CASE_PIPExTRN(4);
	CASE_PIPExTRN(5);
	CASE_PIPExTRN(B);
	CASE_PIPExTRN(C);
	CASE_PIPExTRN(D);
	CASE_PIPExTRN(E);
	CASE_PIPExTRN(F);
	CASE_PIPExTRN(9);
	CASE_PIPExTRN(A);
	default:
		dev_err(dev, "unknown pipe (%d)\n", num);
		return;
	}
	__usbhsp_pipe_xxx_set(pipe, 0, reg, mask, val);
}