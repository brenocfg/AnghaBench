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
typedef  int /*<<< orphan*/  req_file_t ;
typedef  int /*<<< orphan*/  object_header_t ;
struct TYPE_3__ {int /*<<< orphan*/  req_file; } ;
typedef  TYPE_1__ http_request_t ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/ * req_file_addref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD HTTPREQ_LockRequestFile(object_header_t *hdr, req_file_t **ret)
{
    http_request_t *req = (http_request_t*)hdr;

    TRACE("(%p)\n", req);

    if(!req->req_file) {
        WARN("No cache file name available\n");
        return ERROR_FILE_NOT_FOUND;
    }

    *ret = req_file_addref(req->req_file);
    return ERROR_SUCCESS;
}