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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  TDI_STATUS ;
typedef  int /*<<< orphan*/  TDIEntityID ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  TDI_INVALID_REQUEST ; 

TDI_STATUS InfoTransportLayerTdiSetEx( UINT InfoClass,
				       UINT InfoType,
				       UINT InfoId,
				       PVOID Context,
				       TDIEntityID *id,
				       PCHAR Buffer,
				       UINT BufferSize ) {
    return TDI_INVALID_REQUEST;
}