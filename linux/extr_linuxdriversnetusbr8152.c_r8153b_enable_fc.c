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
struct r8152 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UPS_FLAGS_EN_FLOW_CTR ; 
 int /*<<< orphan*/  r8152b_enable_fc (struct r8152*) ; 
 int /*<<< orphan*/  r8153b_ups_flags_w1w0 (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r8153b_enable_fc(struct r8152 *tp)
{
	r8152b_enable_fc(tp);
	r8153b_ups_flags_w1w0(tp, UPS_FLAGS_EN_FLOW_CTR, 0);
}