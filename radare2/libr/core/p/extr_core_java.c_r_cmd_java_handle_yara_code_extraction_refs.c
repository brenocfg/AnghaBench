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
typedef  int ut64 ;
struct TYPE_4__ {int /*<<< orphan*/  fcns; } ;
typedef  int /*<<< orphan*/  RCore ;
typedef  int /*<<< orphan*/  RBinJavaObj ;
typedef  TYPE_1__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* get_anal (int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* r_cmd_java_consumetok (char const*,char,int) ; 
 scalar_t__ r_cmd_java_get_bin_obj (TYPE_1__*) ; 
 int r_cmd_java_get_input_num_value (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ r_cmd_java_is_valid_input_num_value (int /*<<< orphan*/ *,char const*) ; 
 char* r_cmd_java_strtok (char const*,char,int) ; 
 scalar_t__ r_list_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_cmd_java_handle_yara_code_extraction_refs (RCore *core, const char *input) {
	RAnal *anal = get_anal (core);
	RBinJavaObj *bin = anal ? (RBinJavaObj *) r_cmd_java_get_bin_obj (anal) : NULL;
	const char *p = input? r_cmd_java_consumetok (input, ' ', -1): NULL, *n = NULL;
	char *name = NULL;
	ut64 addr = -1, count = -1;
	int res = false;

	if (!bin) {
		return res;
	} else if (!anal || !anal->fcns || r_list_length (anal->fcns) == 0) {
		eprintf ("Unable to access the current analysis, perform 'af' for function analysis.\n");
		return true;
	}

	if (!p) {
		return res;
	}

	n = *p ? r_cmd_java_strtok (p, ' ', -1) : NULL;
	name = n && p && p != n ? malloc (n - p + 2) : NULL;

	if (!name) {
		return res;
	}

	memset (name, 0, n-p);
	memcpy (name, p, n-p);

	p = r_cmd_java_strtok (p, ' ', -1);
	addr = p && *p && r_cmd_java_is_valid_input_num_value(core, p) ? r_cmd_java_get_input_num_value (core, p) : -1;

	p = r_cmd_java_strtok (p, ' ', -1);
	count = p && *p && r_cmd_java_is_valid_input_num_value(core, p) ? r_cmd_java_get_input_num_value (core, p) : -1;

	if (name && count != (ut64) -1 && addr != (ut64) -1) {
		// find function at addr

		// find the start basic block

		// read the bytes

		// hexlify the bytes

		// set the name = bytes

		// print t
	}
	free (name);
	return res;
}