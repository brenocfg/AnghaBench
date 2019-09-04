#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ rbc_ram_start; } ;
struct TYPE_9__ {TYPE_3__ fifo; } ;
struct TYPE_10__ {TYPE_4__ fp; } ;
struct TYPE_7__ {TYPE_1__* m; } ;
struct s_smc {TYPE_5__ hw; TYPE_2__ mib; } ;
struct TYPE_6__ {int /*<<< orphan*/  fddiMACUpstreamNbr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_NPP () ; 
 scalar_t__ DBEACON_FRAME_OFF ; 
 scalar_t__ DBEACON_INFO ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_CMDREG2 ; 
 scalar_t__ FM_ISTTB ; 
 int /*<<< orphan*/  FM_SABC ; 
 size_t MAC0 ; 
 int /*<<< orphan*/  MARW (scalar_t__) ; 
 int /*<<< orphan*/  SK_LOC_DECL (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  __le32 ; 
 scalar_t__* a ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  write_mdr (struct s_smc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void directed_beacon(struct s_smc *smc)
{
	SK_LOC_DECL(__le32,a[2]) ;

	/*
	 * set UNA in frame
	 * enable FORMAC to send endless queue of directed beacon
	 * important: the UNA starts at byte 1 (not at byte 0)
	 */
	* (char *) a = (char) ((long)DBEACON_INFO<<24L) ;
	a[1] = 0 ;
	memcpy((char *)a+1, (char *) &smc->mib.m[MAC0].fddiMACUpstreamNbr, ETH_ALEN);

	CHECK_NPP() ;
	 /* set memory address reg for writes */
	MARW(smc->hw.fp.fifo.rbc_ram_start+DBEACON_FRAME_OFF+4) ;
	write_mdr(smc,le32_to_cpu(a[0])) ;
	outpw(FM_A(FM_CMDREG2),FM_ISTTB) ;	/* set the tag bit */
	write_mdr(smc,le32_to_cpu(a[1])) ;

	outpw(FM_A(FM_SABC),smc->hw.fp.fifo.rbc_ram_start + DBEACON_FRAME_OFF) ;
}