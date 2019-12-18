#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int /*<<< orphan*/  frag_len; } ;
struct TYPE_7__ {TYPE_1__ common; } ;
typedef  TYPE_2__ RpcPktHdr ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  HINTERNET ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  InternetWriteFile (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NDR_LOCAL_DATA_REPRESENTATION ; 
 TYPE_2__* RPCRT4_BuildHttpHeader (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPCRT4_FreeHeader (TYPE_2__*) ; 

__attribute__((used)) static VOID rpcrt4_http_keep_connection_active_timer_proc(PVOID param, BOOLEAN dummy)
{
    HINTERNET in_request = param;
    RpcPktHdr *idle_pkt;

    idle_pkt = RPCRT4_BuildHttpHeader(NDR_LOCAL_DATA_REPRESENTATION, 0x0001,
                                      0, 0);
    if (idle_pkt)
    {
        DWORD bytes_written;
        InternetWriteFile(in_request, idle_pkt, idle_pkt->common.frag_len, &bytes_written);
        RPCRT4_FreeHeader(idle_pkt);
    }
}