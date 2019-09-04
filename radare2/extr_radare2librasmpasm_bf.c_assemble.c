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
typedef  char ut8 ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  int /*<<< orphan*/  RAsm ;

/* Variables and functions */
 int atoi (char const*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  r_strbuf_setbin (int /*<<< orphan*/ *,char*,int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int assemble(RAsm *a, RAsmOp *op, const char *buf) {
	int n = 0;
	if (buf[0] && buf[1] == ' ') {
		buf += 2;
	}
	const char *arg = strchr (buf, ',');
	const char *ref = strchr (buf, '[');
	ut8 opbuf[32];
	if (!strncmp (buf, "trap", 4)) {
		if (arg) {
			n = atoi (arg + 1);
			memset (opbuf, 0xcc, n);
		} else {
			opbuf[0] = 0x90;
			n = 1;
		}
	} else if (!strncmp (buf, "nop", 3))        {
		if (arg) {
			n = atoi (arg + 1);
			memset (opbuf, 0x90, n);
		} else {
			opbuf[0] = 0x90;
			n = 1;
		}
	} else if (!strncmp (buf, "inc", 3))        {
		char ch = ref? '+': '>';
		opbuf[0] = ch;
		n = 1;
	} else if (!strncmp (buf, "dec", 3))        {
		char ch = ref? '-': '<';
		opbuf[0] = ch;
		n = 1;
	} else if (!strncmp (buf, "sub", 3))        {
		char ch = ref? '-': '<';
		if (arg) {
			n = atoi (arg + 1);
			memset (opbuf, ch, n);
		} else {
			opbuf[0] = '<';
			n = 1;
		}
	} else if (!strncmp (buf, "add", 3))        {
		char ch = ref? '+': '>';
		if (arg) {
			n = atoi (arg + 1);
			memset (opbuf, ch, n);
		} else {
			opbuf[0] = '<';
			n = 1;
		}
	} else if (!strncmp (buf, "while", 5))        {
		opbuf[0] = '[';
		n = 1;
	} else if (!strncmp (buf, "loop", 4))        {
		opbuf[0] = ']';
		n = 1;
	} else if (!strncmp (buf, "in", 4))        {
		if (arg) {
			n = atoi (arg + 1);
			memset (opbuf, ',', n);
		} else {
			opbuf[0] = ',';
			n = 1;
		}
	} else if (!strncmp (buf, "out", 4))        {
		if (arg) {
			n = atoi (arg + 1);
			memset (opbuf, '.', n);
		} else {
			opbuf[0] = '.';
			n = 1;
		}
	}
	r_strbuf_setbin (&op->buf, opbuf, n);
	return n;
}