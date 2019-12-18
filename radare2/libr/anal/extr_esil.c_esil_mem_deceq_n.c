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
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  esil_peek_n (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  esil_poke_n (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ r_anal_esil_get_parm (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 char* r_anal_esil_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_anal_esil_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_anal_esil_pushnum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool esil_mem_deceq_n(RAnalEsil *esil, int bits) {
	bool ret = false;
	ut64 s;
	char *off = r_anal_esil_pop (esil);
	char *src = NULL;
	if (off) {
		r_anal_esil_push (esil, off);
		ret = (!!esil_peek_n (esil, bits));
		src = r_anal_esil_pop (esil);
		if (src && r_anal_esil_get_parm (esil, src, &s)) {
			s--;
			r_anal_esil_pushnum (esil, s);
			r_anal_esil_push (esil, off);
			ret &= (!!esil_poke_n (esil, bits));
		} else {
			ret = false;
		}
	}
	if (!ret) {
		ERR ("esil_mem_deceq_n: invalid parameters");
	}
	free (src);
	free (off);
	return ret;
}