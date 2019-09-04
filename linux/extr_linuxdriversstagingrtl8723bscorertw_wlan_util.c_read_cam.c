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
typedef  int u8 ;
typedef  int u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int _ReadCAM (struct adapter*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

void read_cam(struct adapter *padapter, u8 entry, u8 *get_key)
{
	u32 j, addr, cmd;
	addr = entry << 3;

	/* DBG_8192C("********* DUMP CAM Entry_#%02d***************\n", entry); */
	for (j = 0; j < 6; j++) {
		cmd = _ReadCAM(padapter, addr+j);
		/* DBG_8192C("offset:0x%02x => 0x%08x\n", addr+j, cmd); */
		if (j > 1) /* get key from cam */
			memcpy(get_key+(j-2)*4, &cmd, 4);
	}
	/* DBG_8192C("*********************************\n"); */
}