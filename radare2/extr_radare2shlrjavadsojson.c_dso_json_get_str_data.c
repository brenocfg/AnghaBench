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
struct TYPE_3__ {char* data; } ;
typedef  TYPE_1__ DsoJsonStr ;
typedef  int /*<<< orphan*/  DsoJsonObj ;

/* Variables and functions */
 TYPE_1__* dso_json_get_str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char * dso_json_get_str_data (DsoJsonObj *dso_obj) {
	DsoJsonStr * str = dso_json_get_str (dso_obj);
	if (str) return str->data;
	return NULL;
}