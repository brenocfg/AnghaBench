#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* data_stream; scalar_t__ hCacheFile; } ;
typedef  TYPE_2__ http_request_t ;
struct TYPE_11__ {TYPE_1__* vtbl; } ;
struct TYPE_9__ {scalar_t__ (* read ) (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ;scalar_t__ (* end_of_data ) (TYPE_3__*,TYPE_2__*) ;} ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  commit_cache_entry (TYPE_2__*) ; 
 scalar_t__ stub1 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static DWORD read_http_stream(http_request_t *req, BYTE *buf, DWORD size, DWORD *read, BOOL allow_blocking)
{
    DWORD res;

    res = req->data_stream->vtbl->read(req->data_stream, req, buf, size, read, allow_blocking);
    if(res != ERROR_SUCCESS)
        *read = 0;
    assert(*read <= size);

    if(req->hCacheFile) {
        if(*read) {
            BOOL bres;
            DWORD written;

            bres = WriteFile(req->hCacheFile, buf, *read, &written, NULL);
            if(!bres)
                FIXME("WriteFile failed: %u\n", GetLastError());
        }

        if((res == ERROR_SUCCESS && !*read) || req->data_stream->vtbl->end_of_data(req->data_stream, req))
            commit_cache_entry(req);
    }

    return res;
}