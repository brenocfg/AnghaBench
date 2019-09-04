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
struct TYPE_4__ {struct TYPE_4__* elems; } ;
typedef  TYPE_1__ OMF_multi_datas ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (TYPE_1__*) ; 

__attribute__((used)) static void free_pubdef(OMF_multi_datas *datas) {
#if 0
	while (ct_rec < datas->nb_elem) {
		R_FREE (((OMF_symbol *)(datas->elems + ct_rec++))->name);
	}
#endif
	R_FREE (datas->elems);
	R_FREE (datas);
}