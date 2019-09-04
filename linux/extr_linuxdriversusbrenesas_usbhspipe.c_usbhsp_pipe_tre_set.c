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
 int /*<<< orphan*/  PIPE1TRE ; 
 int /*<<< orphan*/  PIPE2TRE ; 
 int /*<<< orphan*/  PIPE3TRE ; 
 int /*<<< orphan*/  PIPE4TRE ; 
 int /*<<< orphan*/  PIPE5TRE ; 
 int /*<<< orphan*/  PIPE9TRE ; 
 int /*<<< orphan*/  PIPEATRE ; 
 int /*<<< orphan*/  PIPEBTRE ; 
 int /*<<< orphan*/  PIPECTRE ; 
 int /*<<< orphan*/  PIPEDTRE ; 
 int /*<<< orphan*/  PIPEETRE ; 
 int /*<<< orphan*/  PIPEFTRE ; 
 int /*<<< orphan*/  __usbhsp_pipe_xxx_set (struct usbhs_pipe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int usbhs_pipe_number (struct usbhs_pipe*) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 

__attribute__((used)) static void usbhsp_pipe_tre_set(struct usbhs_pipe *pipe, u16 mask, u16 val)
{
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	struct device *dev = usbhs_priv_to_dev(priv);
	int num = usbhs_pipe_number(pipe);
	u16 reg;

	/*
	 * It is impossible to calculate address,
	 * since PIPEnTRE addresses were mapped randomly.
	 */
#define CASE_PIPExTRE(a)			\
	case 0x ## a:				\
		reg = PIPE ## a ## TRE;		\
		break;

	switch (num) {
	CASE_PIPExTRE(1);
	CASE_PIPExTRE(2);
	CASE_PIPExTRE(3);
	CASE_PIPExTRE(4);
	CASE_PIPExTRE(5);
	CASE_PIPExTRE(B);
	CASE_PIPExTRE(C);
	CASE_PIPExTRE(D);
	CASE_PIPExTRE(E);
	CASE_PIPExTRE(F);
	CASE_PIPExTRE(9);
	CASE_PIPExTRE(A);
	default:
		dev_err(dev, "unknown pipe (%d)\n", num);
		return;
	}

	__usbhsp_pipe_xxx_set(pipe, 0, reg, mask, val);
}