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
typedef  unsigned long u8 ;
typedef  unsigned long u64 ;
typedef  unsigned long u32 ;
typedef  unsigned long u16 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 

void kvm_mmio_write_buf(void *buf, unsigned int len, unsigned long data)
{
	void *datap = NULL;
	union {
		u8	byte;
		u16	hword;
		u32	word;
		u64	dword;
	} tmp;

	switch (len) {
	case 1:
		tmp.byte	= data;
		datap		= &tmp.byte;
		break;
	case 2:
		tmp.hword	= data;
		datap		= &tmp.hword;
		break;
	case 4:
		tmp.word	= data;
		datap		= &tmp.word;
		break;
	case 8:
		tmp.dword	= data;
		datap		= &tmp.dword;
		break;
	}

	memcpy(buf, datap, len);
}