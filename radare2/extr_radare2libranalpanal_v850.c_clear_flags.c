#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  esil; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 int V850_FLAG_CY ; 
 int V850_FLAG_OV ; 
 int V850_FLAG_S ; 
 int V850_FLAG_Z ; 
 int /*<<< orphan*/  r_strbuf_append (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void clear_flags(RAnalOp *op, int flags) {
	if (flags & V850_FLAG_CY) {
		r_strbuf_append (&op->esil, ",0,cy,=");
	}
	if (flags & V850_FLAG_OV) {
		r_strbuf_append (&op->esil, ",0,ov,=");
	}
	if (flags & V850_FLAG_S) {
		r_strbuf_append (&op->esil, ",0,s,=");
	}
	if (flags & V850_FLAG_Z) {
		r_strbuf_append (&op->esil, ",0,z,=");
	}
}