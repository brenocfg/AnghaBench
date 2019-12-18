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
struct TYPE_3__ {scalar_t__ bom; scalar_t__ readed; } ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  TYPE_1__ BSCallback ;

/* Variables and functions */
 scalar_t__ BOM_NONE ; 
 scalar_t__ BOM_UTF16 ; 
 scalar_t__ BOM_UTF8 ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ *,void*,int,int*) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 

HRESULT read_stream(BSCallback *This, IStream *stream, void *buf, DWORD size, DWORD *ret_size)
{
    DWORD read_size = 0, skip=0;
    BYTE *data = buf;
    HRESULT hres;

    hres = IStream_Read(stream, buf, size, &read_size);

    if(!This->readed && This->bom == BOM_NONE) {
        if(read_size >= 2 && data[0] == 0xff && data[1] == 0xfe) {
            This->bom = BOM_UTF16;
            skip = 2;
        }else if(read_size >= 3 && data[0] == 0xef && data[1] == 0xbb && data[2] == 0xbf) {
            This->bom = BOM_UTF8;
            skip = 3;
        }
        if(skip) {
            read_size -= skip;
            if(read_size)
                memmove(data, data+skip, read_size);
        }
    }

    This->readed += read_size;
    *ret_size = read_size;
    return hres;
}