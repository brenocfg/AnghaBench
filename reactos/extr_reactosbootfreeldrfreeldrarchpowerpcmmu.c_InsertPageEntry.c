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
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GetPhys (int) ; 
 int GetSDR1 () ; 
 int GetSR (int) ; 
 int /*<<< orphan*/  SetPhys (int,int) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN InsertPageEntry( int virt, int phys, int slot, int _sdr1 ) {
    int i, ptehi, ptelo;
    int sdr1 = _sdr1 ? _sdr1 : GetSDR1();
    int sr = GetSR( (virt >> 28) & 0xf );
    int vsid = sr & 0xfffffff;
    int physbase = sdr1 & ~0xffff;
    int hashmask = ((sdr1 & 0x1ff) << 10) | 0x3ff;
    int valo = (vsid << 28) | (virt & 0xfffffff);
    int hash = (vsid & 0x7ffff) ^ ((valo >> 12) & 0xffff);
    int ptegaddr = ((hashmask & hash) * 64) + physbase;

    for( i = 0; i < 8; i++ ) {
    ptehi = GetPhys( ptegaddr + (i * 8) );

    if( (slot != i) && (ptehi & 0x80000000) ) continue;

    ptehi = (1 << 31) | (vsid << 7) | ((virt >> 22) & 0x3f);
    ptelo = phys & ~0xfff;

    SetPhys( ptegaddr + (i * 8), ptehi );
    SetPhys( ptegaddr + (i * 8) + 4, ptelo );

    return TRUE;
    }

    return FALSE;
}