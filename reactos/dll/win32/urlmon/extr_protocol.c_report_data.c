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
struct TYPE_3__ {int flags; int /*<<< orphan*/  content_length; scalar_t__ available_bytes; scalar_t__ current_position; int /*<<< orphan*/  protocol_sink; } ;
typedef  TYPE_1__ Protocol ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BSCF_FIRSTDATANOTIFICATION ; 
 int /*<<< orphan*/  BSCF_INTERMEDIATEDATANOTIFICATION ; 
 int /*<<< orphan*/  BSCF_LASTDATANOTIFICATION ; 
 int FLAG_ALL_DATA_READ ; 
 int FLAG_FIRST_DATA_REPORTED ; 
 int FLAG_LAST_DATA_REPORTED ; 
 int /*<<< orphan*/  IInternetProtocolSink_ReportData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void report_data(Protocol *protocol)
{
    DWORD bscf;

    if((protocol->flags & FLAG_LAST_DATA_REPORTED) || !protocol->protocol_sink)
        return;

    if(protocol->flags & FLAG_FIRST_DATA_REPORTED) {
        bscf = BSCF_INTERMEDIATEDATANOTIFICATION;
    }else {
        protocol->flags |= FLAG_FIRST_DATA_REPORTED;
        bscf = BSCF_FIRSTDATANOTIFICATION;
    }

    if(protocol->flags & FLAG_ALL_DATA_READ && !(protocol->flags & FLAG_LAST_DATA_REPORTED)) {
        protocol->flags |= FLAG_LAST_DATA_REPORTED;
        bscf |= BSCF_LASTDATANOTIFICATION;
    }

    IInternetProtocolSink_ReportData(protocol->protocol_sink, bscf,
            protocol->current_position+protocol->available_bytes,
            protocol->content_length);
}