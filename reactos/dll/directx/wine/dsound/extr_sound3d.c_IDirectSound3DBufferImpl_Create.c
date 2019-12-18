#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_5__* dsb; int /*<<< orphan*/ * lpVtbl; scalar_t__ ref; } ;
struct TYPE_14__ {double x; double y; double z; } ;
struct TYPE_13__ {double x; double y; double z; } ;
struct TYPE_12__ {double x; double y; double z; } ;
struct TYPE_15__ {int dwSize; int /*<<< orphan*/  dwMode; int /*<<< orphan*/  flMaxDistance; int /*<<< orphan*/  flMinDistance; int /*<<< orphan*/  lConeOutsideVolume; TYPE_3__ vConeOrientation; void* dwOutsideConeAngle; void* dwInsideConeAngle; TYPE_2__ vVelocity; TYPE_1__ vPosition; } ;
struct TYPE_16__ {int /*<<< orphan*/  ds3db_need_recalc; TYPE_4__ ds3db_ds3db; } ;
typedef  TYPE_5__ IDirectSoundBufferImpl ;
typedef  TYPE_6__ IDirectSound3DBufferImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DS3DBUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  DS3DMODE_NORMAL ; 
 void* DS3D_DEFAULTCONEANGLE ; 
 int /*<<< orphan*/  DS3D_DEFAULTCONEOUTSIDEVOLUME ; 
 int /*<<< orphan*/  DS3D_DEFAULTMAXDISTANCE ; 
 int /*<<< orphan*/  DS3D_DEFAULTMINDISTANCE ; 
 int /*<<< orphan*/  DSERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_6__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_5__*,TYPE_6__**) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  ds3dbvt ; 

HRESULT IDirectSound3DBufferImpl_Create(
	IDirectSoundBufferImpl *dsb,
	IDirectSound3DBufferImpl **pds3db)
{
	IDirectSound3DBufferImpl *ds3db;
	TRACE("(%p,%p)\n",dsb,pds3db);

	ds3db = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(*ds3db));

	if (ds3db == NULL) {
		WARN("out of memory\n");
		*pds3db = 0;
		return DSERR_OUTOFMEMORY;
	}

	ds3db->ref = 0;
	ds3db->dsb = dsb;
	ds3db->lpVtbl = &ds3dbvt;

	ds3db->dsb->ds3db_ds3db.dwSize = sizeof(DS3DBUFFER);
	ds3db->dsb->ds3db_ds3db.vPosition.x = 0.0;
	ds3db->dsb->ds3db_ds3db.vPosition.y = 0.0;
	ds3db->dsb->ds3db_ds3db.vPosition.z = 0.0;
	ds3db->dsb->ds3db_ds3db.vVelocity.x = 0.0;
	ds3db->dsb->ds3db_ds3db.vVelocity.y = 0.0;
	ds3db->dsb->ds3db_ds3db.vVelocity.z = 0.0;
	ds3db->dsb->ds3db_ds3db.dwInsideConeAngle = DS3D_DEFAULTCONEANGLE;
	ds3db->dsb->ds3db_ds3db.dwOutsideConeAngle = DS3D_DEFAULTCONEANGLE;
	ds3db->dsb->ds3db_ds3db.vConeOrientation.x = 0.0;
	ds3db->dsb->ds3db_ds3db.vConeOrientation.y = 0.0;
	ds3db->dsb->ds3db_ds3db.vConeOrientation.z = 0.0;
	ds3db->dsb->ds3db_ds3db.lConeOutsideVolume = DS3D_DEFAULTCONEOUTSIDEVOLUME;
	ds3db->dsb->ds3db_ds3db.flMinDistance = DS3D_DEFAULTMINDISTANCE;
	ds3db->dsb->ds3db_ds3db.flMaxDistance = DS3D_DEFAULTMAXDISTANCE;
	ds3db->dsb->ds3db_ds3db.dwMode = DS3DMODE_NORMAL;

	ds3db->dsb->ds3db_need_recalc = TRUE;

	*pds3db = ds3db;
	return S_OK;
}