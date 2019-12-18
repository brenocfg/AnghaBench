#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int demanglercmd; } ;

/* Variables and functions */
#define  R_BIN_NM_CXX 133 
#define  R_BIN_NM_JAVA 132 
#define  R_BIN_NM_MSVC 131 
#define  R_BIN_NM_OBJC 130 
#define  R_BIN_NM_RUST 129 
#define  R_BIN_NM_SWIFT 128 
 TYPE_1__* bin ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  file ; 
 char* r_bin_demangle_cxx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* r_bin_demangle_java (int /*<<< orphan*/ ) ; 
 char* r_bin_demangle_msvc (int /*<<< orphan*/ ) ; 
 char* r_bin_demangle_objc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* r_bin_demangle_rust (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* r_bin_demangle_swift (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *__demangleAs(int type) {
	bool syscmd = bin? bin->demanglercmd: false;
	char *res = NULL;
	switch (type) {
	case R_BIN_NM_CXX: res = r_bin_demangle_cxx (NULL, file, 0); break;
	case R_BIN_NM_JAVA: res = r_bin_demangle_java (file); break;
	case R_BIN_NM_OBJC: res = r_bin_demangle_objc (NULL, file); break;
	case R_BIN_NM_SWIFT: res = r_bin_demangle_swift (file, syscmd); break;
	case R_BIN_NM_MSVC: res = r_bin_demangle_msvc (file); break;
	case R_BIN_NM_RUST: res = r_bin_demangle_rust (NULL, file, 0); break;
	default:
		eprintf ("Unsupported demangler\n");
		break;
	}
	return res;
}