#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  wbe2; } ;
struct TYPE_7__ {TYPE_1__ cps; int /*<<< orphan*/  busy; } ;
typedef  TYPE_2__ DocHost ;
typedef  TYPE_3__ DISPPARAMS ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DISPID_DOWNLOADBEGIN ; 
 int /*<<< orphan*/  DISPID_DOWNLOADCOMPLETE ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  VARIANT_FALSE ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 int /*<<< orphan*/  call_sink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

void notify_download_state(DocHost *dochost, BOOL is_downloading)
{
    DISPPARAMS dwl_dp = {NULL};
    TRACE("(%x)\n", is_downloading);
    dochost->busy = is_downloading ? VARIANT_TRUE : VARIANT_FALSE;
    call_sink(dochost->cps.wbe2, is_downloading ? DISPID_DOWNLOADBEGIN : DISPID_DOWNLOADCOMPLETE, &dwl_dp);
}