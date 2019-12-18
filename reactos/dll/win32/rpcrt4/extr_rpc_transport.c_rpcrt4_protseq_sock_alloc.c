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
typedef  int /*<<< orphan*/  WSADATA ;
struct TYPE_3__ {int /*<<< orphan*/  common; int /*<<< orphan*/  mgr_event; } ;
typedef  TYPE_1__ RpcServerProtseq_sock ;
typedef  int /*<<< orphan*/  RpcServerProtseq ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RpcServerProtseq *rpcrt4_protseq_sock_alloc(void)
{
    RpcServerProtseq_sock *ps = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ps));
    if (ps)
    {
        static BOOL wsa_inited;
        if (!wsa_inited)
        {
            WSADATA wsadata;
            WSAStartup(MAKEWORD(2, 2), &wsadata);
            /* Note: WSAStartup can be called more than once so we don't bother with
             * making accesses to wsa_inited thread-safe */
            wsa_inited = TRUE;
        }
        ps->mgr_event = CreateEventW(NULL, FALSE, FALSE, NULL);
    }
    return &ps->common;
}