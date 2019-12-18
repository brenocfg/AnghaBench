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
struct TYPE_3__ {int flags; scalar_t__ protocol_sink; } ;
typedef  TYPE_1__ Protocol ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int FLAG_RESULT_REPORTED ; 
 int /*<<< orphan*/  IInternetProtocolSink_ReportResult (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline HRESULT report_result(Protocol *protocol, HRESULT hres)
{
    if (!(protocol->flags & FLAG_RESULT_REPORTED) && protocol->protocol_sink) {
        protocol->flags |= FLAG_RESULT_REPORTED;
        IInternetProtocolSink_ReportResult(protocol->protocol_sink, hres, 0, NULL);
    }

    return hres;
}