#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_9__ {int lastsz; TYPE_1__* anal; scalar_t__ cur; scalar_t__ old; } ;
struct TYPE_8__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_2__ RAnalEsil ;

/* Variables and functions */
 void* esil_internal_sizeof_reg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ r_anal_esil_get_parm (TYPE_2__*,char*,scalar_t__*) ; 
 char* r_anal_esil_pop (TYPE_2__*) ; 
 int /*<<< orphan*/  r_anal_esil_pushnum (TYPE_2__*,int) ; 
 scalar_t__ r_reg_get (int /*<<< orphan*/ ,char*,int) ; 
 int signed_compare_gt (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static bool esil_bigger_equal(RAnalEsil *esil) { // 'dst >= src' => 'src,dst,>='
	ut64 num, num2;
	bool ret = false;
	char *dst = r_anal_esil_pop (esil);
	char *src = r_anal_esil_pop (esil);
	if (dst && r_anal_esil_get_parm (esil, dst, &num)) {
		if (src && r_anal_esil_get_parm (esil, src, &num2)) {
			esil->old = num;
			esil->cur = num - num2;
			ret = true;
			if (r_reg_get (esil->anal->reg, dst, -1)) {
				esil->lastsz = esil_internal_sizeof_reg (esil, dst);
			} else if (r_reg_get (esil->anal->reg, src, -1)) {
				esil->lastsz = esil_internal_sizeof_reg (esil, src);
			} else {
				// default size is set to 64 as internally operands are ut64
				esil->lastsz = 64;
			}
			r_anal_esil_pushnum (esil, (num == num2) |
			                           signed_compare_gt (num, num2, esil->lastsz));
		}
	}
	free (dst);
	free (src);
	return ret;
}