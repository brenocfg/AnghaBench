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
struct list {int dummy; } ;
struct TYPE_3__ {char* post_data; int post_data_len; int /*<<< orphan*/ * post_stream; scalar_t__* headers; } ;
typedef  TYPE_1__ request_data_t ;
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsISeekableStream ;
typedef  int /*<<< orphan*/  nsIInputStream ;
typedef  scalar_t__ WCHAR ;
typedef  scalar_t__ UINT64 ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 char* GlobalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GlobalFree (char*) ; 
 int /*<<< orphan*/  IID_nsISeekableStream ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__*,int) ; 
 scalar_t__ NS_FAILED (scalar_t__) ; 
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  NS_SEEK_SET ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debugstr_an (char*,int) ; 
 scalar_t__* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (scalar_t__*) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  nsIInputStream_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIInputStream_Available (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ nsIInputStream_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ nsIInputStream_Read (int /*<<< orphan*/ *,char*,scalar_t__,int*) ; 
 int /*<<< orphan*/  nsISeekableStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ nsISeekableStream_Seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_headers (scalar_t__*,struct list*) ; 

__attribute__((used)) static HRESULT read_post_data_stream(nsIInputStream *stream, BOOL contains_headers, struct list *headers_list,
        request_data_t *request_data)
{
    nsISeekableStream *seekable_stream;
    UINT64 available = 0;
    UINT32 data_len = 0;
    char *data, *post_data;
    nsresult nsres;
    HRESULT hres = S_OK;

    if(!stream)
        return S_OK;

    nsres =  nsIInputStream_Available(stream, &available);
    if(NS_FAILED(nsres))
        return E_FAIL;

    post_data = data = GlobalAlloc(0, available+1);
    if(!data)
        return E_OUTOFMEMORY;

    nsres = nsIInputStream_Read(stream, data, available, &data_len);
    if(NS_FAILED(nsres)) {
        GlobalFree(data);
        return E_FAIL;
    }

    if(contains_headers) {
        if(data_len >= 2 && data[0] == '\r' && data[1] == '\n') {
            post_data = data+2;
            data_len -= 2;
        }else {
            WCHAR *headers;
            DWORD size;
            char *ptr;

            post_data += data_len;
            for(ptr = data; ptr+4 < data+data_len; ptr++) {
                if(!memcmp(ptr, "\r\n\r\n", 4)) {
                    ptr += 2;
                    post_data = ptr+2;
                    break;
                }
            }

            data_len -= post_data-data;

            size = MultiByteToWideChar(CP_ACP, 0, data, ptr-data, NULL, 0);
            headers = heap_alloc((size+1)*sizeof(WCHAR));
            if(headers) {
                MultiByteToWideChar(CP_ACP, 0, data, ptr-data, headers, size);
                headers[size] = 0;
                if(headers_list)
                    hres = parse_headers(headers, headers_list);
                if(SUCCEEDED(hres))
                    request_data->headers = headers;
                else
                    heap_free(headers);
            }else {
                hres = E_OUTOFMEMORY;
            }
        }
    }

    if(FAILED(hres)) {
        GlobalFree(data);
        return hres;
    }

    if(!data_len) {
        GlobalFree(data);
        post_data = NULL;
    }else if(post_data != data) {
        char *new_data;

        new_data = GlobalAlloc(0, data_len+1);
        if(new_data)
            memcpy(new_data, post_data, data_len);
        GlobalFree(data);
        if(!new_data)
            return E_OUTOFMEMORY;
        post_data = new_data;
    }

    if(post_data)
        post_data[data_len] = 0;
    request_data->post_data = post_data;
    request_data->post_data_len = data_len;

    nsres = nsIInputStream_QueryInterface(stream, &IID_nsISeekableStream, (void**)&seekable_stream);
    assert(nsres == NS_OK);

    nsres = nsISeekableStream_Seek(seekable_stream, NS_SEEK_SET, 0);
    assert(nsres == NS_OK);

    nsISeekableStream_Release(seekable_stream);

    nsIInputStream_AddRef(stream);
    request_data->post_stream = stream;
    TRACE("post_data = %s\n", debugstr_an(request_data->post_data, request_data->post_data_len));
    return S_OK;
}