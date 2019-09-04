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
typedef  int /*<<< orphan*/  RAnalClassErr ;
typedef  int /*<<< orphan*/  RAnalClassAttrType ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_CLASS_ERR_OTHER ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_anal_class_add_attr_unique_raw (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,char*,size_t) ; 
 char* r_str_sanitize_sdb_key (char const*) ; 

__attribute__((used)) static RAnalClassErr r_anal_class_add_attr_unique(RAnal *anal, const char *class_name, RAnalClassAttrType attr_type, const char *content, char *attr_id_out, size_t attr_id_out_size) {
	char *class_name_sanitized = r_str_sanitize_sdb_key (class_name);
	if (!class_name_sanitized) {
		return R_ANAL_CLASS_ERR_OTHER;
	}

	RAnalClassErr err = r_anal_class_add_attr_unique_raw (anal, class_name_sanitized, attr_type, content, attr_id_out, attr_id_out_size);

	free (class_name_sanitized);
	return err;
}