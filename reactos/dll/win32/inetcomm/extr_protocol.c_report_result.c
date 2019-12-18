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
struct TYPE_3__ {int /*<<< orphan*/ * sink; } ;
typedef  TYPE_1__ MimeHtmlProtocol ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  IInternetProtocolSink_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IInternetProtocolSink_ReportResult (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT report_result(MimeHtmlProtocol *protocol, HRESULT result)
{
    if(protocol->sink) {
        IInternetProtocolSink_ReportResult(protocol->sink, result, ERROR_SUCCESS, NULL);
        IInternetProtocolSink_Release(protocol->sink);
        protocol->sink = NULL;
    }

    return result;
}