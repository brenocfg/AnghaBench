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
typedef  int /*<<< orphan*/  ut32 ;
typedef  int /*<<< orphan*/  RIDStorage ;

/* Variables and functions */
 char* condrets_strtok (char*,char) ; 
 scalar_t__ r_id_storage_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esil_expr_atomize(RIDStorage *atoms, char *expr) {
	ut32 forget_me;
	for (
		; !!expr && r_id_storage_add (atoms, expr, &forget_me);
		expr = condrets_strtok (expr, ',')) {
	}
}