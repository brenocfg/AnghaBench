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
struct kparam_array {unsigned int* num; unsigned int max; unsigned int elemsize; scalar_t__ elem; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void param_array_free(void *arg)
{
	unsigned int i;
	const struct kparam_array *arr = arg;

	if (arr->ops->free)
		for (i = 0; i < (arr->num ? *arr->num : arr->max); i++)
			arr->ops->free(arr->elem + arr->elemsize * i);
}