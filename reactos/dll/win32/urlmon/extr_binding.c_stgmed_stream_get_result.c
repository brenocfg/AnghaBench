#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stgmed_obj_t ;
struct TYPE_4__ {int /*<<< orphan*/  IStream_iface; TYPE_1__* buf; } ;
struct TYPE_3__ {scalar_t__ file; scalar_t__ hres; } ;
typedef  TYPE_2__ ProtocolStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int BINDF_ASYNCHRONOUS ; 
 int /*<<< orphan*/  INET_E_DATA_NOT_AVAILABLE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IStream_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT stgmed_stream_get_result(stgmed_obj_t *obj, DWORD bindf, void **result)
{
    ProtocolStream *stream = (ProtocolStream*)obj;

    if(!(bindf & BINDF_ASYNCHRONOUS) && stream->buf->file == INVALID_HANDLE_VALUE
       && stream->buf->hres != S_FALSE)
        return INET_E_DATA_NOT_AVAILABLE;

    IStream_AddRef(&stream->IStream_iface);
    *result = &stream->IStream_iface;
    return S_OK;
}