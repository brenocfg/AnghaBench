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
struct q6afe_port {int dummy; } ;
struct afe_clk_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_MODULE_CLOCK_SET ; 
 int /*<<< orphan*/  AFE_PARAM_ID_CLOCK_SET ; 
 int q6afe_port_set_param (struct q6afe_port*,struct afe_clk_set*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int q6afe_set_lpass_clock_v2(struct q6afe_port *port,
				 struct afe_clk_set *cfg)
{
	return q6afe_port_set_param(port, cfg, AFE_PARAM_ID_CLOCK_SET,
				    AFE_MODULE_CLOCK_SET, sizeof(*cfg));
}