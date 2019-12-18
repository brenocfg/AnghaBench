#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int refs; TYPE_2__ IUnknown_iface; int /*<<< orphan*/ * typelib_base; } ;
typedef  TYPE_1__ TLB_NEFile ;
typedef  int /*<<< orphan*/  OFSTRUCT ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  scalar_t__ LPCWSTR ;
typedef  TYPE_2__ IUnknown ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ HFILE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ IMAGE_OS2_SIGNATURE ; 
 int /*<<< orphan*/  LZClose (scalar_t__) ; 
 scalar_t__ LZOpenFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int LZRead (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LZSeek (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_READ ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TLB_NEFile_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  TLB_NEFile_Vtable ; 
 int /*<<< orphan*/  TYPE_E_CANTLOADLIBRARY ; 
 scalar_t__ find_ne_resource (scalar_t__,char*,int /*<<< orphan*/ ,int*,int*) ; 
 void* heap_alloc (int) ; 
 scalar_t__ read_xx_header (scalar_t__) ; 

__attribute__((used)) static HRESULT TLB_NEFile_Open(LPCWSTR path, INT index, LPVOID *ppBase, DWORD *pdwTLBLength, IUnknown **ppFile){

    HFILE lzfd = -1;
    OFSTRUCT ofs;
    HRESULT hr = TYPE_E_CANTLOADLIBRARY;
    TLB_NEFile *This;

    This = heap_alloc(sizeof(TLB_NEFile));
    if (!This) return E_OUTOFMEMORY;

    This->IUnknown_iface.lpVtbl = &TLB_NEFile_Vtable;
    This->refs = 1;
    This->typelib_base = NULL;

    lzfd = LZOpenFileW( (LPWSTR)path, &ofs, OF_READ );
    if ( lzfd >= 0 && read_xx_header( lzfd ) == IMAGE_OS2_SIGNATURE )
    {
        DWORD reslen, offset;
        if( find_ne_resource( lzfd, "TYPELIB", MAKEINTRESOURCEA(index), &reslen, &offset ) )
        {
            This->typelib_base = heap_alloc(reslen);
            if( !This->typelib_base )
                hr = E_OUTOFMEMORY;
            else
            {
                LZSeek( lzfd, offset, SEEK_SET );
                reslen = LZRead( lzfd, This->typelib_base, reslen );
                LZClose( lzfd );
                *ppBase = This->typelib_base;
                *pdwTLBLength = reslen;
                *ppFile = &This->IUnknown_iface;
                return S_OK;
            }
        }
    }

    if( lzfd >= 0) LZClose( lzfd );
    TLB_NEFile_Release(&This->IUnknown_iface);
    return hr;
}