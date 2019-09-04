#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  (* build_zero_len_sge_mpi ) (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ *) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  IOCStatus; } ;
struct TYPE_9__ {int /*<<< orphan*/  PageVersion; scalar_t__ PageNumber; int /*<<< orphan*/  PageType; } ;
struct TYPE_11__ {int /*<<< orphan*/  Action; int /*<<< orphan*/  PageBufferSGE; TYPE_1__ Header; int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  Function; } ;
struct TYPE_10__ {int /*<<< orphan*/  NumPhys; } ;
typedef  TYPE_2__ Mpi2SasIOUnitPage0_t ;
typedef  TYPE_3__ Mpi2ConfigRequest_t ;
typedef  TYPE_4__ Mpi2ConfigReply_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPI2_CONFIG_ACTION_PAGE_HEADER ; 
 int /*<<< orphan*/  MPI2_CONFIG_ACTION_PAGE_READ_CURRENT ; 
 int /*<<< orphan*/  MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT ; 
 int /*<<< orphan*/  MPI2_CONFIG_PAGETYPE_EXTENDED ; 
 int /*<<< orphan*/  MPI2_FUNCTION_CONFIG ; 
 int MPI2_IOCSTATUS_MASK ; 
 int MPI2_IOCSTATUS_SUCCESS ; 
 int /*<<< orphan*/  MPI2_SASIOUNITPAGE0_PAGEVERSION ; 
 int /*<<< orphan*/  MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT ; 
 int _config_request (struct MPT3SAS_ADAPTER*,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ *) ; 

int
mpt3sas_config_get_number_hba_phys(struct MPT3SAS_ADAPTER *ioc, u8 *num_phys)
{
	Mpi2ConfigRequest_t mpi_request;
	int r;
	u16 ioc_status;
	Mpi2ConfigReply_t mpi_reply;
	Mpi2SasIOUnitPage0_t config_page;

	*num_phys = 0;
	memset(&mpi_request, 0, sizeof(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT;
	mpi_request.Header.PageNumber = 0;
	mpi_request.Header.PageVersion = MPI2_SASIOUNITPAGE0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, &mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, NULL, 0);
	if (r)
		goto out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, &mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, &config_page,
	    sizeof(Mpi2SasIOUnitPage0_t));
	if (!r) {
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		if (ioc_status == MPI2_IOCSTATUS_SUCCESS)
			*num_phys = config_page.NumPhys;
	}
 out:
	return r;
}