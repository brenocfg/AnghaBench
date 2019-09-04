#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ut32 ;
typedef  scalar_t__ ut16 ;
struct TYPE_7__ {int /*<<< orphan*/  class_idx; } ;
struct TYPE_8__ {TYPE_1__ cp_method; } ;
struct TYPE_9__ {scalar_t__ tag; TYPE_2__ info; } ;
typedef  int /*<<< orphan*/  RCore ;
typedef  int /*<<< orphan*/  RBinJavaObj ;
typedef  TYPE_3__ RBinJavaCPTypeObj ;

/* Variables and functions */
 scalar_t__ R_BIN_JAVA_CP_FIELDREF ; 
 scalar_t__ R_BIN_JAVA_CP_INTERFACEMETHOD_REF ; 
 scalar_t__ R_BIN_JAVA_CP_METHODREF ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 char* r_bin_java_get_item_desc_from_bin_cp_list (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* r_bin_java_get_item_from_bin_cp_list (int /*<<< orphan*/ *,scalar_t__) ; 
 char* r_bin_java_get_item_name_from_bin_cp_list (int /*<<< orphan*/ *,TYPE_3__*) ; 
 char* r_bin_java_get_name_from_bin_cp_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* r_bin_java_unmangle_without_flags (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 char* strdup (char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char * r_cmd_java_get_descriptor (RCore *core, RBinJavaObj *bin, ut16 idx) {
	char *class_name = NULL, *fullname = NULL, *name = NULL, *descriptor = NULL;
	RBinJavaCPTypeObj * obj = r_bin_java_get_item_from_bin_cp_list (bin, idx);
	char * prototype = NULL;
	if (idx == 0) {
		prototype = strdup ("NULL");
		return prototype;
	}

	if (obj->tag == R_BIN_JAVA_CP_INTERFACEMETHOD_REF ||
		obj->tag == R_BIN_JAVA_CP_METHODREF ||
		obj->tag == R_BIN_JAVA_CP_FIELDREF) {
		class_name = r_bin_java_get_name_from_bin_cp_list (bin, obj->info.cp_method.class_idx);
		name = r_bin_java_get_item_name_from_bin_cp_list (bin, obj);
		descriptor = r_bin_java_get_item_desc_from_bin_cp_list (bin, obj);
	}

	if (class_name && name) {
		ut32 fn_len = 0;
		fn_len += strlen (class_name);
		fn_len += strlen (name);
		fn_len += 2; // dot + null
		fullname = malloc (fn_len);
		snprintf (fullname, fn_len, "%s.%s", class_name, name);
	}
	if (fullname) {
		prototype = r_bin_java_unmangle_without_flags (fullname, descriptor);
	}
	free (class_name);
	free (name);
	free (descriptor);
	free (fullname);
	return prototype;
}