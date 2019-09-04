#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * json_dict; } ;
typedef  TYPE_1__ DsoJsonDict ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 

void dso_json_dict_free (void *y) {
	DsoJsonDict *x = (DsoJsonDict *)y;
	if (x && x->json_dict) {
		r_list_free (x->json_dict);
		x->json_dict = NULL;
	}
	free (x);
}