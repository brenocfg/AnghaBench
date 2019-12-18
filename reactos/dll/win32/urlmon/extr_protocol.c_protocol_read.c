#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_5__ {int flags; scalar_t__ available_bytes; scalar_t__ query_available; int /*<<< orphan*/  request; int /*<<< orphan*/  current_position; } ;
typedef  TYPE_1__ Protocol ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_IO_PENDING ; 
 scalar_t__ E_PENDING ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int FLAG_ALL_DATA_READ ; 
 int FLAG_REQUEST_COMPLETE ; 
 int FLAG_SYNC_READ ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INET_E_DATA_NOT_AVAILABLE ; 
 scalar_t__ INET_E_DOWNLOAD_FAILURE ; 
 int /*<<< orphan*/  InternetQueryDataAvailable (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InternetReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 int /*<<< orphan*/  all_data_read (TYPE_1__*) ; 
 int /*<<< orphan*/  report_result (TYPE_1__*,scalar_t__) ; 

HRESULT protocol_read(Protocol *protocol, void *buf, ULONG size, ULONG *read_ret)
{
    ULONG read = 0;
    BOOL res;
    HRESULT hres = S_FALSE;

    if(protocol->flags & FLAG_ALL_DATA_READ) {
        *read_ret = 0;
        return S_FALSE;
    }

    if(!(protocol->flags & FLAG_SYNC_READ) && (!(protocol->flags & FLAG_REQUEST_COMPLETE) || !protocol->available_bytes)) {
        *read_ret = 0;
        return E_PENDING;
    }

    while(read < size && protocol->available_bytes) {
        ULONG len;

        res = InternetReadFile(protocol->request, ((BYTE *)buf)+read,
                protocol->available_bytes > size-read ? size-read : protocol->available_bytes, &len);
        if(!res) {
            WARN("InternetReadFile failed: %d\n", GetLastError());
            hres = INET_E_DOWNLOAD_FAILURE;
            report_result(protocol, hres);
            break;
        }

        if(!len) {
            all_data_read(protocol);
            break;
        }

        read += len;
        protocol->current_position += len;
        protocol->available_bytes -= len;

        TRACE("current_position %d, available_bytes %d\n", protocol->current_position, protocol->available_bytes);

        if(!protocol->available_bytes) {
            /* InternetQueryDataAvailable may immediately fork and perform its asynchronous
             * read, so clear the flag _before_ calling so it does not incorrectly get cleared
             * after the status callback is called */
            protocol->flags &= ~FLAG_REQUEST_COMPLETE;
            res = InternetQueryDataAvailable(protocol->request, &protocol->query_available, 0, 0);
            if(!res) {
                if (GetLastError() == ERROR_IO_PENDING) {
                    hres = E_PENDING;
                }else {
                    WARN("InternetQueryDataAvailable failed: %d\n", GetLastError());
                    hres = INET_E_DATA_NOT_AVAILABLE;
                    report_result(protocol, hres);
                }
                break;
            }

            if(!protocol->query_available) {
                all_data_read(protocol);
                break;
            }

            protocol->available_bytes = protocol->query_available;
        }
    }

    *read_ret = read;

    if (hres != E_PENDING)
        protocol->flags |= FLAG_REQUEST_COMPLETE;
    if(FAILED(hres))
        return hres;

    return read ? S_OK : S_FALSE;
}