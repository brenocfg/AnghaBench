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

__attribute__((used)) static int __esil_pop_argument(RAnalEsil *esil, ut64 *v) {
	char *t = r_anal_esil_pop (esil);
	if (!t || !r_anal_esil_get_parm (esil, t, v)) {
		free (t);
		return false;
	}
	free (t);
	return true;
}