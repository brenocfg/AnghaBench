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
struct ns2_pinctrl {struct ns2_mux_log* mux_log; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int shift; scalar_t__ alt; scalar_t__ offset; void* base; } ;
struct ns2_mux_log {int is_configured; TYPE_1__ mux; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NS2_MUX_PAD_FUNC1_OFFSET ; 
 unsigned int NS2_NUM_IOMUX ; 
 unsigned int NS2_NUM_PWM_MUX ; 
 void* NS2_PIN_MUX_BASE0 ; 
 void* NS2_PIN_MUX_BASE1 ; 
 struct ns2_mux_log* devm_kcalloc (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ns2_mux_log_init(struct ns2_pinctrl *pinctrl)
{
	struct ns2_mux_log *log;
	unsigned int i;

	pinctrl->mux_log = devm_kcalloc(pinctrl->dev, NS2_NUM_IOMUX,
					sizeof(struct ns2_mux_log),
					GFP_KERNEL);
	if (!pinctrl->mux_log)
		return -ENOMEM;

	for (i = 0; i < NS2_NUM_IOMUX; i++)
		pinctrl->mux_log[i].is_configured = false;
	/* Group 0 uses bit 31 in the IOMUX_PAD_FUNCTION_0 register */
	log = &pinctrl->mux_log[0];
	log->mux.base = NS2_PIN_MUX_BASE0;
	log->mux.offset = 0;
	log->mux.shift = 31;
	log->mux.alt = 0;

	/*
	 * Groups 1 through 14 use two bits each in the
	 * IOMUX_PAD_FUNCTION_1 register starting with
	 * bit position 30.
	 */
	for (i = 1; i < (NS2_NUM_IOMUX - NS2_NUM_PWM_MUX); i++) {
		log = &pinctrl->mux_log[i];
		log->mux.base = NS2_PIN_MUX_BASE0;
		log->mux.offset = NS2_MUX_PAD_FUNC1_OFFSET;
		log->mux.shift = 32 - (i * 2);
		log->mux.alt = 0;
	}

	/*
	 * Groups 15 through 18 use one bit each in the
	 * AUX_SEL register.
	 */
	for (i = 0; i < NS2_NUM_PWM_MUX; i++) {
		log = &pinctrl->mux_log[(NS2_NUM_IOMUX - NS2_NUM_PWM_MUX) + i];
		log->mux.base = NS2_PIN_MUX_BASE1;
		log->mux.offset = 0;
		log->mux.shift = i;
		log->mux.alt =  0;
	}
	return 0;
}