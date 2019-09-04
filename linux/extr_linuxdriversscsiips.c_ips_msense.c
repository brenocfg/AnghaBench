#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  mdata ;
struct TYPE_22__ {size_t target_id; TYPE_11__* scsi_cmd; } ;
typedef  TYPE_7__ ips_scb_t ;
struct TYPE_23__ {TYPE_1__* enq; } ;
typedef  TYPE_8__ ips_ha_t ;
struct TYPE_20__ {int PageCode; int PageLength; } ;
struct TYPE_18__ {int PageCode; int PageLength; int CylindersLow; int Heads; int /*<<< orphan*/  MediumRotationRate; int /*<<< orphan*/  RotationalOffset; int /*<<< orphan*/  flags; int /*<<< orphan*/  LandingZoneLow; int /*<<< orphan*/  LandingZoneHigh; void* StepRate; int /*<<< orphan*/  ReducedWriteCurrentLow; int /*<<< orphan*/  ReducedWriteCurrentHigh; int /*<<< orphan*/  WritePrecompLow; int /*<<< orphan*/  WritePrecompHigh; void* CylindersHigh; } ;
struct TYPE_17__ {int PageCode; int PageLength; int /*<<< orphan*/  flags; int /*<<< orphan*/  CylinderSkew; int /*<<< orphan*/  TrackSkew; void* Interleave; void* BytesPerSector; void* SectorsPerTrack; int /*<<< orphan*/  AltTracksPerVolume; int /*<<< orphan*/  AltTracksPerZone; int /*<<< orphan*/  AltSectorsPerZone; int /*<<< orphan*/  TracksPerZone; } ;
struct TYPE_21__ {TYPE_5__ pg8; TYPE_3__ pg4; TYPE_2__ pg3; } ;
struct TYPE_19__ {int BlockDescLength; int DataLength; } ;
struct TYPE_24__ {TYPE_6__ pdata; TYPE_4__ hdr; } ;
struct TYPE_16__ {int ucMiscFlag; int /*<<< orphan*/ * ulDriveSize; } ;
struct TYPE_15__ {int* cmnd; } ;
typedef  TYPE_9__ IPS_SCSI_MODE_PAGE_DATA ;
typedef  int /*<<< orphan*/  IPS_SCSI_MODE_PAGE8 ;
typedef  int /*<<< orphan*/  IPS_SCSI_MODE_PAGE4 ;
typedef  int /*<<< orphan*/  IPS_SCSI_MODE_PAGE3 ;

/* Variables and functions */
 int IPS_BLKSIZE ; 
 int IPS_COMP_HEADS ; 
 int IPS_COMP_SECTORS ; 
 int IPS_NORM_HEADS ; 
 int IPS_NORM_SECTORS ; 
 int /*<<< orphan*/  IPS_SCSI_MP3_SoftSector ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  ips_scmd_buf_write (TYPE_11__*,TYPE_9__*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ips_msense(ips_ha_t * ha, ips_scb_t * scb)
{
	uint16_t heads;
	uint16_t sectors;
	uint32_t cylinders;
	IPS_SCSI_MODE_PAGE_DATA mdata;

	METHOD_TRACE("ips_msense", 1);

	if (le32_to_cpu(ha->enq->ulDriveSize[scb->target_id]) > 0x400000 &&
	    (ha->enq->ucMiscFlag & 0x8) == 0) {
		heads = IPS_NORM_HEADS;
		sectors = IPS_NORM_SECTORS;
	} else {
		heads = IPS_COMP_HEADS;
		sectors = IPS_COMP_SECTORS;
	}

	cylinders =
	    (le32_to_cpu(ha->enq->ulDriveSize[scb->target_id]) -
	     1) / (heads * sectors);

	memset(&mdata, 0, sizeof (IPS_SCSI_MODE_PAGE_DATA));

	mdata.hdr.BlockDescLength = 8;

	switch (scb->scsi_cmd->cmnd[2] & 0x3f) {
	case 0x03:		/* page 3 */
		mdata.pdata.pg3.PageCode = 3;
		mdata.pdata.pg3.PageLength = sizeof (IPS_SCSI_MODE_PAGE3);
		mdata.hdr.DataLength =
		    3 + mdata.hdr.BlockDescLength + mdata.pdata.pg3.PageLength;
		mdata.pdata.pg3.TracksPerZone = 0;
		mdata.pdata.pg3.AltSectorsPerZone = 0;
		mdata.pdata.pg3.AltTracksPerZone = 0;
		mdata.pdata.pg3.AltTracksPerVolume = 0;
		mdata.pdata.pg3.SectorsPerTrack = cpu_to_be16(sectors);
		mdata.pdata.pg3.BytesPerSector = cpu_to_be16(IPS_BLKSIZE);
		mdata.pdata.pg3.Interleave = cpu_to_be16(1);
		mdata.pdata.pg3.TrackSkew = 0;
		mdata.pdata.pg3.CylinderSkew = 0;
		mdata.pdata.pg3.flags = IPS_SCSI_MP3_SoftSector;
		break;

	case 0x4:
		mdata.pdata.pg4.PageCode = 4;
		mdata.pdata.pg4.PageLength = sizeof (IPS_SCSI_MODE_PAGE4);
		mdata.hdr.DataLength =
		    3 + mdata.hdr.BlockDescLength + mdata.pdata.pg4.PageLength;
		mdata.pdata.pg4.CylindersHigh =
		    cpu_to_be16((cylinders >> 8) & 0xFFFF);
		mdata.pdata.pg4.CylindersLow = (cylinders & 0xFF);
		mdata.pdata.pg4.Heads = heads;
		mdata.pdata.pg4.WritePrecompHigh = 0;
		mdata.pdata.pg4.WritePrecompLow = 0;
		mdata.pdata.pg4.ReducedWriteCurrentHigh = 0;
		mdata.pdata.pg4.ReducedWriteCurrentLow = 0;
		mdata.pdata.pg4.StepRate = cpu_to_be16(1);
		mdata.pdata.pg4.LandingZoneHigh = 0;
		mdata.pdata.pg4.LandingZoneLow = 0;
		mdata.pdata.pg4.flags = 0;
		mdata.pdata.pg4.RotationalOffset = 0;
		mdata.pdata.pg4.MediumRotationRate = 0;
		break;
	case 0x8:
		mdata.pdata.pg8.PageCode = 8;
		mdata.pdata.pg8.PageLength = sizeof (IPS_SCSI_MODE_PAGE8);
		mdata.hdr.DataLength =
		    3 + mdata.hdr.BlockDescLength + mdata.pdata.pg8.PageLength;
		/* everything else is left set to 0 */
		break;

	default:
		return (0);
	}			/* end switch */

	ips_scmd_buf_write(scb->scsi_cmd, &mdata, sizeof (mdata));

	return (1);
}