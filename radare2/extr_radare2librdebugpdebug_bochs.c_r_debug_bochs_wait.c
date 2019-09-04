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
struct TYPE_3__ {char* data; } ;
typedef  int /*<<< orphan*/  RDebug ;

/* Variables and functions */
 int bBreak ; 
 int bStep ; 
 int /*<<< orphan*/  bochs_debug_break ; 
 int /*<<< orphan*/  bochs_wait (TYPE_1__*) ; 
 TYPE_1__* desc ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  isBochs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_break_pop () ; 
 int /*<<< orphan*/  r_cons_break_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ r_num_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ripStop ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 void* strstr (char const*,char*) ; 

__attribute__((used)) static int r_debug_bochs_wait(RDebug *dbg, int pid) {
	if (!isBochs (dbg)) {
		return false;
	}
	char strIP[19];
	int i = 0;
	const char *x;
	char *ini = 0, *fin = 0;

	//eprintf ("bochs_wait:\n");

	if (bStep) {
		bStep = false;
	} else {
		r_cons_break_push (bochs_debug_break, dbg);
		i = 500;
		do {
			bochs_wait (desc);
			if (bBreak) {
				if (desc->data[0]) {
					eprintf ("ctrl+c %s\n", desc->data);
					bBreak = false;
					break;
				}
				i--;
				if (!i) {
					bBreak = false;
					eprintf ("empty ctrl+c.\n");
					break;
				}
			} else if (desc->data[0]) {
				//eprintf("stop on breakpoint%s\n",desc->data);
				break;
			}
		} while(1);
		r_cons_break_pop ();
	}
	//eprintf ("bochs_wait: loop done\n");
	// Next at t=394241428
	// (0) [0x000000337635] 0020:0000000000337635 (unk. ctxt): add eax, esi              ; 03c6
	ripStop = 0;
	if ((x = strstr (desc->data, "Next at"))) {
		if ((ini = strstr (x, "[0x"))) {
			if ((fin = strstr (ini,"]"))) {
				int len = fin - ini - 1;
				strncpy (strIP, ini+1, len);
				strIP[len] = 0;
				//eprintf(" parada EIP = %s\n",strIP);
				ripStop = r_num_get (NULL, strIP);
			}
		}
	}
	desc->data[0] = 0;

	return true;
}