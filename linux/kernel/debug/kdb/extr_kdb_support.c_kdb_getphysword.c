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
typedef  int /*<<< orphan*/  w8 ;
typedef  int /*<<< orphan*/  w4 ;
typedef  int /*<<< orphan*/  w2 ;
typedef  int /*<<< orphan*/  w1 ;
typedef  unsigned long __u8 ;
typedef  unsigned long __u64 ;
typedef  unsigned long __u32 ;
typedef  unsigned long __u16 ;

/* Variables and functions */
 int KDB_BADWIDTH ; 
 int kdb_getphys (unsigned long*,unsigned long,int) ; 
 int /*<<< orphan*/  kdb_printf (char*,long) ; 

int kdb_getphysword(unsigned long *word, unsigned long addr, size_t size)
{
	int diag;
	__u8  w1;
	__u16 w2;
	__u32 w4;
	__u64 w8;
	*word = 0;	/* Default value if addr or size is invalid */

	switch (size) {
	case 1:
		diag = kdb_getphys(&w1, addr, sizeof(w1));
		if (!diag)
			*word = w1;
		break;
	case 2:
		diag = kdb_getphys(&w2, addr, sizeof(w2));
		if (!diag)
			*word = w2;
		break;
	case 4:
		diag = kdb_getphys(&w4, addr, sizeof(w4));
		if (!diag)
			*word = w4;
		break;
	case 8:
		if (size <= sizeof(*word)) {
			diag = kdb_getphys(&w8, addr, sizeof(w8));
			if (!diag)
				*word = w8;
			break;
		}
		/* fall through */
	default:
		diag = KDB_BADWIDTH;
		kdb_printf("kdb_getphysword: bad width %ld\n", (long) size);
	}
	return diag;
}