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
typedef  int /*<<< orphan*/  DsoJsonObj ;

/* Variables and functions */
 int dso_json_dict_contains_key_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso_json_get_str_data (int /*<<< orphan*/ *) ; 

int dso_json_dict_contains_key_obj (DsoJsonObj *dict, DsoJsonObj *key) {
	return dso_json_dict_contains_key_str (dict, dso_json_get_str_data (key));
}