#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct nsp_pinctrl {struct nsp_mux_log* mux_log; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {scalar_t__ alt; int /*<<< orphan*/  shift; int /*<<< orphan*/  base; } ;
struct nsp_mux_log {int is_configured; TYPE_2__ mux; } ;
struct TYPE_5__ {int /*<<< orphan*/  shift; int /*<<< orphan*/  base; } ;
struct TYPE_7__ {TYPE_1__ mux; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_3__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nsp_mux_log* devm_kcalloc (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* nsp_pin_groups ; 

__attribute__((used)) static int nsp_mux_log_init(struct nsp_pinctrl *pinctrl)
{
	struct nsp_mux_log *log;
	unsigned int i;
	u32 no_of_groups = ARRAY_SIZE(nsp_pin_groups);

	pinctrl->mux_log = devm_kcalloc(pinctrl->dev, no_of_groups,
					sizeof(struct nsp_mux_log),
					GFP_KERNEL);
	if (!pinctrl->mux_log)
		return -ENOMEM;

	for (i = 0; i < no_of_groups; i++) {
		log = &pinctrl->mux_log[i];
		log->mux.base = nsp_pin_groups[i].mux.base;
		log->mux.shift = nsp_pin_groups[i].mux.shift;
		log->mux.alt = 0;
		log->is_configured = false;
	}

	return 0;
}