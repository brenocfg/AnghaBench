#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  TYPE_1__* sdlParamPtr ;
struct TYPE_4__ {struct TYPE_4__* paramName; } ;

/* Variables and functions */
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (TYPE_1__*) ; 

__attribute__((used)) static void delete_parameter(zval *zv)
{
	sdlParamPtr param = Z_PTR_P(zv);
	if (param->paramName) {
		efree(param->paramName);
	}
	efree(param);
}