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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_anal_esil_get_parm (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 char* r_anal_esil_pop (int /*<<< orphan*/ *) ; 
 int r_anal_esil_pushnum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool esil_num(RAnalEsil *esil) {
	char *dup_me;
	ut64 dup;
	if (!esil) {
		return false;
	}
	if (!(dup_me = r_anal_esil_pop (esil))) {
		return false;
	}
	if (!r_anal_esil_get_parm (esil, dup_me, &dup)) {
		free (dup_me);
		return false;
	}
	free (dup_me);
	return r_anal_esil_pushnum (esil, dup);
}