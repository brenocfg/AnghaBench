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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_3__ {int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  int /*<<< orphan*/  CPU_MODEL ;
typedef  TYPE_1__ CPU_CONST ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CONST_REG ; 
 TYPE_1__* const_by_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * r_strbuf_new (char*) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static RStrBuf *__generic_io_dest(ut8 port, int write, CPU_MODEL *cpu) {
	RStrBuf *r = r_strbuf_new ("");
	CPU_CONST *c = const_by_value (cpu, CPU_CONST_REG, port);
	if (c != NULL) {
		r_strbuf_set (r, c->key);
		if (write) {
			r_strbuf_append (r, ",=");
		}
	} else {
		r_strbuf_setf (r, "_io,%d,+,%s[1]", port, write ? "=" : "");
	}

	return r;
}