#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * lpVtbl; } ;
struct ddraw_clipper {int ref; TYPE_1__ IDirectDrawClipper_iface; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DD_OK ; 
 int /*<<< orphan*/  ddraw_clipper_vtbl ; 

HRESULT ddraw_clipper_init(struct ddraw_clipper *clipper)
{
    clipper->IDirectDrawClipper_iface.lpVtbl = &ddraw_clipper_vtbl;
    clipper->ref = 1;

    return DD_OK;
}