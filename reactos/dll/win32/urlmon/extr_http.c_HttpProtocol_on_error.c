#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; } ;
typedef  TYPE_1__ Protocol ;
typedef  int /*<<< orphan*/  HttpProtocol ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_IO_PENDING ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int FLAG_FIRST_CONTINUE_COMPLETE ; 
 int /*<<< orphan*/  RPC_E_RETRY ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_http_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * impl_from_Protocol (TYPE_1__*) ; 
 int /*<<< orphan*/  protocol_abort (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  protocol_close_connection (TYPE_1__*) ; 
 int /*<<< orphan*/  send_http_request (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HttpProtocol_on_error(Protocol *prot, DWORD error)
{
    HttpProtocol *This = impl_from_Protocol(prot);
    HRESULT hres;

    TRACE("(%p) %d\n", prot, error);

    if(prot->flags & FLAG_FIRST_CONTINUE_COMPLETE) {
        FIXME("Not handling error %d\n", error);
        return;
    }

    while((hres = handle_http_error(This, error)) == RPC_E_RETRY) {
        error = send_http_request(This);

        if(error == ERROR_IO_PENDING || error == ERROR_SUCCESS)
            return;
    }

    protocol_abort(prot, hres);
    protocol_close_connection(prot);
    return;
}