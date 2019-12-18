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
typedef  int /*<<< orphan*/  size ;
typedef  char WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  pStorage; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/ * LPCSTR ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  TYPE_1__ CHMInfo ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetChmString (TYPE_1__*,int) ; 
 int /*<<< orphan*/  IStorage_OpenStream (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ *,int*,int,int*) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STGM_READ ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (int /*<<< orphan*/ *) ; 
 int* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int*) ; 
 int /*<<< orphan*/ * strdupAtoW (int /*<<< orphan*/ *) ; 

LPWSTR FindContextAlias(CHMInfo *chm, DWORD index)
{
    IStream *ivb_stream;
    DWORD size, read, i;
    DWORD *buf;
    LPCSTR ret = NULL;
    HRESULT hres;

    static const WCHAR wszIVB[] = {'#','I','V','B',0};

    hres = IStorage_OpenStream(chm->pStorage, wszIVB, NULL, STGM_READ, 0, &ivb_stream);
    if(FAILED(hres)) {
        WARN("Could not open #IVB stream: %08x\n", hres);
        return NULL;
    }

    hres = IStream_Read(ivb_stream, &size, sizeof(size), &read);
    if(FAILED(hres)) {
        WARN("Read failed: %08x\n", hres);
        IStream_Release(ivb_stream);
        return NULL;
    }

    buf = heap_alloc(size);
    hres = IStream_Read(ivb_stream, buf, size, &read);
    IStream_Release(ivb_stream);
    if(FAILED(hres)) {
        WARN("Read failed: %08x\n", hres);
        heap_free(buf);
        return NULL;
    }

    size /= 2*sizeof(DWORD);

    for(i=0; i<size; i++) {
        if(buf[2*i] == index) {
            ret = GetChmString(chm, buf[2*i+1]);
            break;
        }
    }

    heap_free(buf);

    TRACE("returning %s\n", debugstr_a(ret));
    return strdupAtoW(ret);
}