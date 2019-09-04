#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int frmerr; int unxfrm; int nosync; int diperr; int datovr; int ovrbst; int calpar1; int calpar0; } ;
union cvmx_stxx_int_msk {void* u64; TYPE_2__ s; } ;
struct TYPE_3__ {int calerr; int syncerr; int diperr; int tpaovr; int rsverr; int drwnng; int clserr; int spiovr; int abnorm; int prtnxa; } ;
union cvmx_spxx_int_msk {void* u64; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SPXX_INT_MSK (int) ; 
 int /*<<< orphan*/  CVMX_STXX_INT_MSK (int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void cvm_oct_spi_enable_error_reporting(int interface)
{
	union cvmx_spxx_int_msk spxx_int_msk;
	union cvmx_stxx_int_msk stxx_int_msk;

	spxx_int_msk.u64 = cvmx_read_csr(CVMX_SPXX_INT_MSK(interface));
	spxx_int_msk.s.calerr = 1;
	spxx_int_msk.s.syncerr = 1;
	spxx_int_msk.s.diperr = 1;
	spxx_int_msk.s.tpaovr = 1;
	spxx_int_msk.s.rsverr = 1;
	spxx_int_msk.s.drwnng = 1;
	spxx_int_msk.s.clserr = 1;
	spxx_int_msk.s.spiovr = 1;
	spxx_int_msk.s.abnorm = 1;
	spxx_int_msk.s.prtnxa = 1;
	cvmx_write_csr(CVMX_SPXX_INT_MSK(interface), spxx_int_msk.u64);

	stxx_int_msk.u64 = cvmx_read_csr(CVMX_STXX_INT_MSK(interface));
	stxx_int_msk.s.frmerr = 1;
	stxx_int_msk.s.unxfrm = 1;
	stxx_int_msk.s.nosync = 1;
	stxx_int_msk.s.diperr = 1;
	stxx_int_msk.s.datovr = 1;
	stxx_int_msk.s.ovrbst = 1;
	stxx_int_msk.s.calpar1 = 1;
	stxx_int_msk.s.calpar0 = 1;
	cvmx_write_csr(CVMX_STXX_INT_MSK(interface), stxx_int_msk.u64);
}