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
struct pxa_pinctrl_function {scalar_t__ name; } ;
struct pxa_pinctrl {int npins; int nfuncs; int /*<<< orphan*/  dev; int /*<<< orphan*/  functions; TYPE_1__* ppins; } ;
struct pxa_desc_function {scalar_t__ name; } ;
struct TYPE_2__ {struct pxa_desc_function* functions; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pxa_pinctrl_function* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct pxa_pinctrl_function*) ; 
 int /*<<< orphan*/  devm_kmemdup (int /*<<< orphan*/ ,struct pxa_pinctrl_function*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa2xx_find_function (struct pxa_pinctrl*,scalar_t__,struct pxa_pinctrl_function*) ; 

__attribute__((used)) static int pxa2xx_build_functions(struct pxa_pinctrl *pctl)
{
	int i;
	struct pxa_pinctrl_function *functions;
	struct pxa_desc_function *df;

	/*
	 * Each pin can have at most 6 alternate functions, and 2 gpio functions
	 * which are common to each pin. As there are more than 2 pins without
	 * alternate function, 6 * npins is an absolute high limit of the number
	 * of functions.
	 */
	functions = devm_kcalloc(pctl->dev, pctl->npins * 6,
				 sizeof(*functions), GFP_KERNEL);
	if (!functions)
		return -ENOMEM;

	for (i = 0; i < pctl->npins; i++)
		for (df = pctl->ppins[i].functions; df->name; df++)
			if (!pxa2xx_find_function(pctl, df->name, functions))
				(functions + pctl->nfuncs++)->name = df->name;
	pctl->functions = devm_kmemdup(pctl->dev, functions,
				       pctl->nfuncs * sizeof(*functions),
				       GFP_KERNEL);
	if (!pctl->functions)
		return -ENOMEM;

	devm_kfree(pctl->dev, functions);
	return 0;
}