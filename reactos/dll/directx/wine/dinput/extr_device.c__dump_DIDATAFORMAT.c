#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int dwSize; int dwObjSize; int dwFlags; unsigned int dwNumObjs; TYPE_1__* rgodf; int /*<<< orphan*/  dwDataSize; } ;
struct TYPE_4__ {int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  dwType; int /*<<< orphan*/  dwOfs; int /*<<< orphan*/  pguid; } ;
typedef  int /*<<< orphan*/  DIOBJECTDATAFORMAT ;
typedef  TYPE_2__ DIDATAFORMAT ;

/* Variables and functions */
#define  DIDF_ABSAXIS 129 
#define  DIDF_RELAXIS 128 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  _dump_EnumObjects_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _dump_ObjectDataFormat_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _dump_dinput_GUID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 

void _dump_DIDATAFORMAT(const DIDATAFORMAT *df) {
    unsigned int i;

    TRACE("Dumping DIDATAFORMAT structure:\n");
    TRACE("  - dwSize: %d\n", df->dwSize);
    if (df->dwSize != sizeof(DIDATAFORMAT)) {
        WARN("Non-standard DIDATAFORMAT structure size %d\n", df->dwSize);
    }
    TRACE("  - dwObjsize: %d\n", df->dwObjSize);
    if (df->dwObjSize != sizeof(DIOBJECTDATAFORMAT)) {
        WARN("Non-standard DIOBJECTDATAFORMAT structure size %d\n", df->dwObjSize);
    }
    TRACE("  - dwFlags: 0x%08x (", df->dwFlags);
    switch (df->dwFlags) {
        case DIDF_ABSAXIS: TRACE("DIDF_ABSAXIS"); break;
	case DIDF_RELAXIS: TRACE("DIDF_RELAXIS"); break;
	default: TRACE("unknown"); break;
    }
    TRACE(")\n");
    TRACE("  - dwDataSize: %d\n", df->dwDataSize);
    TRACE("  - dwNumObjs: %d\n", df->dwNumObjs);
    
    for (i = 0; i < df->dwNumObjs; i++) {
	TRACE("  - Object %d:\n", i);
	TRACE("      * GUID: %s ('%s')\n", debugstr_guid(df->rgodf[i].pguid), _dump_dinput_GUID(df->rgodf[i].pguid));
        TRACE("      * dwOfs: %d\n", df->rgodf[i].dwOfs);
        TRACE("      * dwType: 0x%08x\n", df->rgodf[i].dwType);
	TRACE("        "); _dump_EnumObjects_flags(df->rgodf[i].dwType); TRACE("\n");
        TRACE("      * dwFlags: 0x%08x\n", df->rgodf[i].dwFlags);
	TRACE("        "); _dump_ObjectDataFormat_flags(df->rgodf[i].dwFlags); TRACE("\n");
    }
}