#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* cur; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* disassemble ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  TYPE_2__ RAsm ;

/* Variables and functions */
 int /*<<< orphan*/  cd ; 
 char* cs_insn_name (int /*<<< orphan*/ ,int) ; 
 char* r_str_newf (char*,char const*) ; 
 int /*<<< orphan*/  r_strbuf_append (int /*<<< orphan*/ *,char const*) ; 
 char* r_strbuf_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_strbuf_new (char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *mnemonics(RAsm *a, int id, bool json) {
	int i;
	a->cur->disassemble (a, NULL, NULL, -1);
	if (id != -1) {
		const char *name = cs_insn_name (cd, id);
		if (json) {
			return name? r_str_newf ("[\"%s\"]\n", name): NULL;
		}
		return name? strdup (name): NULL;
	}
	RStrBuf *buf = r_strbuf_new ("");
	if (json) {
		r_strbuf_append (buf, "[");
	}
	for (i = 1; ; i++) {
		const char *op = cs_insn_name (cd, i);
		if (!op) {
			break;
		}
		if (json) {
			r_strbuf_append (buf, "\"");
		}
		r_strbuf_append (buf, op);
		if (json) {
			if (cs_insn_name (cd, i + 1)) {
				r_strbuf_append (buf, "\",");
			} else {
				r_strbuf_append (buf, "\"]\n");
			}
		} else {
			r_strbuf_append (buf, "\n");
		}
	}
	return r_strbuf_drain (buf);
}