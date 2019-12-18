#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Socket; int /*<<< orphan*/ * fnCompletion; int /*<<< orphan*/  fCommandLogging; int /*<<< orphan*/  Status; int /*<<< orphan*/ * pCallback; } ;
typedef  TYPE_1__ InternetTransport ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IXP_DISCONNECTED ; 
 int /*<<< orphan*/  S_OK ; 

HRESULT InternetTransport_Init(InternetTransport *This)
{
    This->pCallback = NULL;
    This->Status = IXP_DISCONNECTED;
    This->Socket = -1;
    This->fCommandLogging = FALSE;
    This->fnCompletion = NULL;

    return S_OK;
}