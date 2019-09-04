#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  demanglercmd; int /*<<< orphan*/  cur; } ;
struct TYPE_5__ {TYPE_2__* bin; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
#define  R_BIN_NM_CXX 133 
#define  R_BIN_NM_DLANG 132 
#define  R_BIN_NM_JAVA 131 
#define  R_BIN_NM_MSVC 130 
#define  R_BIN_NM_OBJC 129 
#define  R_BIN_NM_SWIFT 128 
 int /*<<< orphan*/  free (char*) ; 
 char* r_bin_demangle_cxx (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 char* r_bin_demangle_java (char const*) ; 
 int /*<<< orphan*/  r_bin_demangle_list (TYPE_2__*) ; 
 char* r_bin_demangle_msvc (char const*) ; 
 char* r_bin_demangle_objc (int /*<<< orphan*/ *,char const*) ; 
 char* r_bin_demangle_plugin (TYPE_2__*,char*,char const*) ; 
 char* r_bin_demangle_swift (char const*,int /*<<< orphan*/ ) ; 
 int r_bin_demangle_type (char const*) ; 
 int /*<<< orphan*/  r_cons_printf (char*,char*) ; 

__attribute__((used)) static bool demangle_internal(RCore *core, const char *lang, const char *s) {
	char *res = NULL;
	int type = r_bin_demangle_type (lang);
	switch (type) {
	case R_BIN_NM_CXX: res = r_bin_demangle_cxx (core->bin->cur, s, 0); break;
	case R_BIN_NM_JAVA: res = r_bin_demangle_java (s); break;
	case R_BIN_NM_OBJC: res = r_bin_demangle_objc (NULL, s); break;
	case R_BIN_NM_SWIFT: res = r_bin_demangle_swift (s, core->bin->demanglercmd); break;
	case R_BIN_NM_DLANG: res = r_bin_demangle_plugin (core->bin, "dlang", s); break;
	case R_BIN_NM_MSVC: res = r_bin_demangle_msvc (s); break;
	default:
		r_bin_demangle_list (core->bin);
		return true;
	}
	if (res) {
		if (*res) {
			r_cons_printf ("%s\n", res);
		}
		free (res);
		return false;
	}
	return true;
}