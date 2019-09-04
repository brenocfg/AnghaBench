#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {int len; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  big_endian; } ;
struct TYPE_6__ {int size; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  TYPE_2__ RAsm ;

/* Variables and functions */
 TYPE_3__* dalvik_opcodes ; 
 int /*<<< orphan*/  r_strbuf_setbin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_write_ble32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int dalvik_assemble(RAsm *a, RAsmOp *op, const char *buf) {
	int i;
	char *p = strchr (buf, ' ');
	if (p) {
		*p = 0;
	}
	// TODO: use a hashtable here
	for (i = 0; i < 256; i++) {
		if (!strcmp (dalvik_opcodes[i].name, buf)) {
			ut8 buf[4];
			r_write_ble32 (buf, i, a->big_endian);
			r_strbuf_setbin (&op->buf, buf, sizeof (buf));
			op->size = dalvik_opcodes[i].len;
			return op->size;
		}
	}
	return 0;
}