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
typedef  int /*<<< orphan*/  CType ;
typedef  int /*<<< orphan*/  AttributeDef ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_ABSTRACT ; 
 int /*<<< orphan*/  expect (char*) ; 
 int /*<<< orphan*/  parse_btype (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_decl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_type(CType *type) {
	AttributeDef ad;
	int n;

	if (!parse_btype (type, &ad)) {
		expect ("type");
	}
	type_decl (type, &ad, &n, TYPE_ABSTRACT);
}