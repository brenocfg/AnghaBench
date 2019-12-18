#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  object_header_t ;
struct TYPE_10__ {TYPE_1__* DebugInfo; } ;
struct TYPE_8__ {size_t nCustHeaders; TYPE_4__* custHeaders; int /*<<< orphan*/  data_stream; TYPE_4__* statusText; TYPE_4__* version; TYPE_4__* verb; TYPE_4__* path; scalar_t__ proxy; scalar_t__ server; int /*<<< orphan*/  proxyAuthInfo; int /*<<< orphan*/  authInfo; TYPE_2__* session; TYPE_5__ read_section; TYPE_5__ headers_section; scalar_t__ req_file; scalar_t__ hCacheFile; } ;
typedef  TYPE_3__ http_request_t ;
struct TYPE_9__ {struct TYPE_9__* lpszValue; struct TYPE_9__* lpszField; } ;
struct TYPE_7__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_6__ {scalar_t__* Spare; } ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  DeleteCriticalSection (TYPE_5__*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WININET_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_authinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_data_stream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (TYPE_4__*) ; 
 int /*<<< orphan*/  req_file_release (scalar_t__) ; 
 int /*<<< orphan*/  server_release (scalar_t__) ; 

__attribute__((used)) static void HTTPREQ_Destroy(object_header_t *hdr)
{
    http_request_t *request = (http_request_t*) hdr;
    DWORD i;

    TRACE("\n");

    if(request->hCacheFile)
        CloseHandle(request->hCacheFile);
    if(request->req_file)
        req_file_release(request->req_file);

    request->headers_section.DebugInfo->Spare[0] = 0;
    DeleteCriticalSection( &request->headers_section );
    request->read_section.DebugInfo->Spare[0] = 0;
    DeleteCriticalSection( &request->read_section );
    WININET_Release(&request->session->hdr);

    destroy_authinfo(request->authInfo);
    destroy_authinfo(request->proxyAuthInfo);

    if(request->server)
        server_release(request->server);
    if(request->proxy)
        server_release(request->proxy);

    heap_free(request->path);
    heap_free(request->verb);
    heap_free(request->version);
    heap_free(request->statusText);

    for (i = 0; i < request->nCustHeaders; i++)
    {
        heap_free(request->custHeaders[i].lpszField);
        heap_free(request->custHeaders[i].lpszValue);
    }
    destroy_data_stream(request->data_stream);
    heap_free(request->custHeaders);
}