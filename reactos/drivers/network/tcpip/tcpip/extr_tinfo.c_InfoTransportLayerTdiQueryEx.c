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
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  Temp ;
typedef  int /*<<< orphan*/  TDI_STATUS ;
typedef  int /*<<< orphan*/  TDIEntityID ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PUINT ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;
typedef  int /*<<< orphan*/  PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CL_TL_UDP ; 
 scalar_t__ ENTITY_TYPE_ID ; 
 scalar_t__ INFO_CLASS_GENERIC ; 
 scalar_t__ INFO_TYPE_PROVIDER ; 
 int /*<<< orphan*/  InfoCopyOut (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDI_INVALID_REQUEST ; 

TDI_STATUS InfoTransportLayerTdiQueryEx( UINT InfoClass,
					 UINT InfoType,
					 UINT InfoId,
					 PVOID Context,
					 TDIEntityID *id,
					 PNDIS_BUFFER Buffer,
					 PUINT BufferSize ) {
    if( InfoClass == INFO_CLASS_GENERIC &&
	InfoType == INFO_TYPE_PROVIDER &&
	InfoId == ENTITY_TYPE_ID ) {
	ULONG Temp = CL_TL_UDP;
	return InfoCopyOut( (PCHAR)&Temp, sizeof(Temp), Buffer, BufferSize );
    }

    return TDI_INVALID_REQUEST;
}