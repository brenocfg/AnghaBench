#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* ut64 ;
struct TYPE_9__ {int lastsz; void* cur; void* old; } ;
typedef  TYPE_1__ RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  esil_peek_n (TYPE_1__*,int) ; 
 int /*<<< orphan*/  esil_poke_n (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ r_anal_esil_get_parm (TYPE_1__*,char*,void**) ; 
 char* r_anal_esil_pop (TYPE_1__*) ; 
 int /*<<< orphan*/  r_anal_esil_push (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  r_anal_esil_pushnum (TYPE_1__*,void*) ; 

__attribute__((used)) static bool esil_mem_inceq_n(RAnalEsil *esil, int bits) {
	bool ret = false;
	ut64 s;
	char *off = r_anal_esil_pop (esil);
	char *src = NULL;
	if (off) {
		r_anal_esil_push (esil, off);
		ret = (!!esil_peek_n (esil, bits));
		src = r_anal_esil_pop (esil);
		if (src && r_anal_esil_get_parm (esil, src, &s)) {
			esil->old = s;
			s++;
			esil->cur = s;
			esil->lastsz = bits;
			r_anal_esil_pushnum (esil, s);
			r_anal_esil_push (esil, off);
			ret &= (!!esil_poke_n (esil, bits));
		} else {
			ret = false;
		}
	}
	if (!ret) {
		ERR ("esil_mem_inceq_n: invalid parameters");
	}
	free (src);
	free (off);
	return ret;
}