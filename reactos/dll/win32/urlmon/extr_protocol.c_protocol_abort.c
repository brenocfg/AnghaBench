#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  protocol_sink; } ;
typedef  TYPE_1__ Protocol ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int FLAG_RESULT_REPORTED ; 
 int /*<<< orphan*/  INET_E_RESULT_DISPATCHED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  report_result (TYPE_1__*,int /*<<< orphan*/ ) ; 

HRESULT protocol_abort(Protocol *protocol, HRESULT reason)
{
    if(!protocol->protocol_sink)
        return S_OK;

    /* NOTE: IE10 returns S_OK here */
    if(protocol->flags & FLAG_RESULT_REPORTED)
        return INET_E_RESULT_DISPATCHED;

    report_result(protocol, reason);
    return S_OK;
}