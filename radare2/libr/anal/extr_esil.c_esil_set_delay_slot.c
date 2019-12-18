#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_5__ {int /*<<< orphan*/  delay; } ;
typedef  TYPE_1__ RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  R_FREE (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ r_anal_esil_get_parm (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 char* r_anal_esil_pop (TYPE_1__*) ; 

__attribute__((used)) static bool esil_set_delay_slot(RAnalEsil *esil) {
	bool ret = false;
	ut64 s;
	char *src = r_anal_esil_pop (esil);
	if (src && r_anal_esil_get_parm (esil, src, &s)) {
		esil->delay = s;
		ret = true;
	} else {
		R_FREE (src);
		ERR ("esil_set_delay_slot: empty stack");
	}
	free (src);
	return ret;
}