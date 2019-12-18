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
struct TYPE_3__ {scalar_t__ json_dict; } ;
typedef  TYPE_1__ DsoJsonDict ;

/* Variables and functions */
 char* build_str_from_str_list_for_iterable (scalar_t__,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 

char * dso_json_dict_to_str (DsoJsonDict *dict) {
	if (dict && dict->json_dict) {
		return build_str_from_str_list_for_iterable (dict->json_dict, 0);
	}
	return strdup ("{}");
}