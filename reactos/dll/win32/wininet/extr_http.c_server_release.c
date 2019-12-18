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
struct TYPE_4__ {struct TYPE_4__* scheme_host_port; struct TYPE_4__* name; scalar_t__ cert_chain; int /*<<< orphan*/  entry; int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ server_t ;

/* Variables and functions */
 int /*<<< orphan*/  CertFreeCertificateChain (scalar_t__) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connection_pool_cs ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

void server_release(server_t *server)
{
    if(InterlockedDecrement(&server->ref))
        return;

#ifdef __REACTOS__
    EnterCriticalSection(&connection_pool_cs);
#endif
    list_remove(&server->entry);
#ifdef __REACTOS__
    LeaveCriticalSection(&connection_pool_cs);
#endif

    if(server->cert_chain)
        CertFreeCertificateChain(server->cert_chain);
    heap_free(server->name);
    heap_free(server->scheme_host_port);
    heap_free(server);
}