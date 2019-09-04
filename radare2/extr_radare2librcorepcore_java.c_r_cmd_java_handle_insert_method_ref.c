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
typedef  int ut32 ;
struct TYPE_4__ {int /*<<< orphan*/  fcns; } ;
typedef  int /*<<< orphan*/  RCore ;
typedef  int /*<<< orphan*/  RBinJavaObj ;
typedef  TYPE_1__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* get_anal (int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 
 char* r_cmd_java_consumetok (char const*,char,int) ; 
 scalar_t__ r_cmd_java_get_bin_obj (TYPE_1__*) ; 
 char* r_cmd_java_strtok (char const*,char,int) ; 
 int /*<<< orphan*/  r_cons_printf (char*,char*,char*,char*) ; 
 scalar_t__ r_list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int r_cmd_java_handle_insert_method_ref (RCore *core, const char *input) {
	RAnal *anal = get_anal (core);
	RBinJavaObj *bin = anal ? (RBinJavaObj *) r_cmd_java_get_bin_obj (anal) : NULL;
	const char *p = input? r_cmd_java_consumetok (input, ' ', -1): NULL, *n = NULL;
	char  *classname=NULL, *name = NULL, *descriptor = NULL;
	ut32 cn_sz = 0, n_sz = 0, d_sz = 0;
	int res = false;

	if (!bin) {
		return res;
	}
	if (!anal || !anal->fcns || r_list_length (anal->fcns) == 0) {
		eprintf ("Unable to access the current analysis, perform 'af' for function analysis.\n");
		return true;
	}
	if (!p) {
		return res;
	}

	n = p && *p ? r_cmd_java_strtok (p, ' ', -1) : NULL;
	classname = n && p && p != n ? malloc (n-p+1) : NULL;
	cn_sz = n && p ? n-p +1 : 0;
	if (!classname) {
		return res;
	}

	snprintf (classname, cn_sz, "%s", p);
	//memset (classname, 0, cn_sz);
	//memcpy (classname, p, n-p);
	p = n+1;
	n = p && *p ? r_cmd_java_strtok (p, ' ', -1) : NULL;
	name = n && p && p != n ? malloc (n-p+1) : NULL;
	n_sz = n && p ? n-p +1 : 0;
	if (!name) {
		free (classname);
		return res;
	}
	snprintf (name, n_sz, "%s", p);
	//memset (name, 0, n_sz);
	//memcpy (name, p, n-p);

	p = n + 1;
	n =  p && *p ? r_cmd_java_strtok (p, ' ', -1) : NULL;
	if (n) {
		descriptor = n && p && p != n ? malloc (n-p+1) : NULL;
		d_sz = n-p +1;
	} else if (p && *p) {
		d_sz = strlen (p) + 1;
		descriptor = d_sz > 1 ? malloc (d_sz) : NULL;
	}

	if (!descriptor) {
		free (classname);
		free (name);
		return res;
	}
	snprintf (descriptor, d_sz, "%s", p);
	//memset (descriptor, 0, d_sz);
	//memcpy (descriptor, p, n-p);

	r_cons_printf ("Would be adding class name:%s, name: %s, descriptor: %s\n", classname, name, descriptor);
	free (classname);
	free (name);
	free (descriptor);
	res = true;
	return res;
}