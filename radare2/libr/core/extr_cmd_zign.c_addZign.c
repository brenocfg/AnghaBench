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
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
#define  R_SIGN_ANAL 138 
#define  R_SIGN_BBHASH 137 
#define  R_SIGN_BYTES 136 
#define  R_SIGN_COMMENT 135 
#define  R_SIGN_GRAPH 134 
#define  R_SIGN_NAME 133 
#define  R_SIGN_OFFSET 132 
#define  R_SIGN_REFS 131 
#define  R_SIGN_TYPES 130 
#define  R_SIGN_VARS 129 
#define  R_SIGN_XREFS 128 
 int addBytesZign (int /*<<< orphan*/ *,char const*,int,char const*,int) ; 
 int addCommentZign (int /*<<< orphan*/ *,char const*,char const*,int) ; 
 int addGraphZign (int /*<<< orphan*/ *,char const*,char const*,int) ; 
 int addHashZign (int /*<<< orphan*/ *,char const*,int,char const*,int) ; 
 int addNameZign (int /*<<< orphan*/ *,char const*,char const*,int) ; 
 int addOffsetZign (int /*<<< orphan*/ *,char const*,char const*,int) ; 
 int addRefsZign (int /*<<< orphan*/ *,char const*,char const*,int) ; 
 int addTypesZign (int /*<<< orphan*/ *,char const*,char const*,int) ; 
 int addVarsZign (int /*<<< orphan*/ *,char const*,char const*,int) ; 
 int addXRefsZign (int /*<<< orphan*/ *,char const*,char const*,int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 

__attribute__((used)) static bool addZign(RCore *core, const char *name, int type, const char *args0, int nargs) {
	switch (type) {
	case R_SIGN_BYTES:
	case R_SIGN_ANAL:
		return addBytesZign (core, name, type, args0, nargs);
	case R_SIGN_GRAPH:
		return addGraphZign (core, name, args0, nargs);
	case R_SIGN_COMMENT:
		return addCommentZign (core, name, args0, nargs);
	case R_SIGN_NAME:
		return addNameZign (core, name, args0, nargs);
	case R_SIGN_OFFSET:
		return addOffsetZign (core, name, args0, nargs);
	case R_SIGN_REFS:
		return addRefsZign (core, name, args0, nargs);
	case R_SIGN_XREFS:
		return addXRefsZign (core, name, args0, nargs);
	case R_SIGN_VARS:
		return addVarsZign (core, name, args0, nargs);
	case R_SIGN_TYPES:
		return addTypesZign (core, name, args0, nargs);
	case R_SIGN_BBHASH:
		return addHashZign (core, name, type, args0, nargs);
	default:
		eprintf ("error: unknown zignature type\n");
	}

	return false;
}