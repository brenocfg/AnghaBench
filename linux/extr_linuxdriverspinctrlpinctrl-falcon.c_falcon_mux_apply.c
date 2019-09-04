#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_dev {int dummy; } ;
struct ltq_pinmux_info {TYPE_1__* mfp; int /*<<< orphan*/ * membase; } ;
struct TYPE_2__ {int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  LTQ_PADC_MUX (int /*<<< orphan*/ ) ; 
 int PORT (int /*<<< orphan*/ ) ; 
 int PORTS ; 
 int /*<<< orphan*/  PORT_PIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pad_w32 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ltq_pinmux_info* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static inline int falcon_mux_apply(struct pinctrl_dev *pctrldev,
			int mfp, int mux)
{
	struct ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);
	int port = PORT(info->mfp[mfp].pin);

	if ((port >= PORTS) || (!info->membase[port]))
		return -ENODEV;

	pad_w32(info->membase[port], mux,
		LTQ_PADC_MUX(PORT_PIN(info->mfp[mfp].pin)));
	return 0;
}