#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ut64 ;
typedef  int ut32 ;
typedef  int /*<<< orphan*/  bufcmd ;
struct TYPE_6__ {char* data; } ;
struct TYPE_5__ {int addr; } ;
typedef  TYPE_1__ RBreakpointItem ;
typedef  int /*<<< orphan*/  RBreakpoint ;

/* Variables and functions */
 int bCapturaRegs ; 
 int /*<<< orphan*/  bochs_send_cmd (TYPE_3__*,char*,int) ; 
 TYPE_3__* desc ; 
 void* r_num_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int r_debug_bochs_breakpoint (RBreakpoint *bp, RBreakpointItem *b, bool set) {
	char cmd[64];
	char num[4];
	char addr[19];
	char bufcmd[100];
	ut64 a;
	int  n,i,lenRec;
	//eprintf ("bochs_breakpoint\n");
	if (!b) {
		return false;
	}
	if (set) {
		//eprintf("[set] bochs_breakpoint %016"PFMT64x"\n",bp->addr);
		sprintf (cmd, "lb 0x%x", (ut32)b->addr);
		bochs_send_cmd (desc, cmd, true);
		bCapturaRegs = true;
	} else {
		//eprintf("[unset] bochs_breakpoint %016"PFMT64x"\n",bp->addr);
		/*
		Num Type           Disp Enb Address
		  1 lbreakpoint    keep y   0x0000000000007c00
		  2 lbreakpoint    keep y   0x0000000000007c00
		<bochs:39>
		*/
		bochs_send_cmd (desc,"blist",true);
		lenRec = strlen (desc->data);
		a = -1;
		n = 0;
		if (!strncmp (desc->data, "Num Type", 8)) {
			i = 37;
			do {
				if (desc->data[i + 24] == 'y') {
					strncpy(num, &desc->data[i], 3);
					num[3] = 0;
					strncpy(addr, &desc->data[i + 28], 18);
					addr[18] = 0;
					n = r_num_get (NULL,num);
					a = r_num_get (NULL,addr);
					//eprintf("parseado %x %016"PFMT64x"\n",n,a);
					if (a == b->addr) {
						break;
					}
				}
				i += 48;
			} while (desc->data[i] != '<' && i<lenRec-4);
		}
		if (a == b->addr) {
			snprintf (bufcmd, sizeof (bufcmd), "d %i", n);
			//eprintf("[unset] Break point localizado indice = %x (%x) %s \n",n,(DWORD)a,bufcmd);
			bochs_send_cmd (desc, bufcmd, true);
		}

	}
	return true;
}