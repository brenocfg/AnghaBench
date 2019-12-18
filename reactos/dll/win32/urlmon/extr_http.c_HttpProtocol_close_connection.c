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
struct TYPE_3__ {int /*<<< orphan*/ * full_header; int /*<<< orphan*/ * http_negotiate; } ;
typedef  int /*<<< orphan*/  Protocol ;
typedef  TYPE_1__ HttpProtocol ;

/* Variables and functions */
 int /*<<< orphan*/  IHttpNegotiate_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* impl_from_Protocol (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HttpProtocol_close_connection(Protocol *prot)
{
    HttpProtocol *This = impl_from_Protocol(prot);

    if(This->http_negotiate) {
        IHttpNegotiate_Release(This->http_negotiate);
        This->http_negotiate = NULL;
    }

    heap_free(This->full_header);
    This->full_header = NULL;
}