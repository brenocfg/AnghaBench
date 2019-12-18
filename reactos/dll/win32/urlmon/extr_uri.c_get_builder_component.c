#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  char* LPWSTR ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  E_POINTER ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static HRESULT get_builder_component(LPWSTR *component, DWORD *component_len,
                                     LPCWSTR source, DWORD source_len,
                                     LPCWSTR *output, DWORD *output_len)
{
    if(!output_len) {
        if(output)
            *output = NULL;
        return E_POINTER;
    }

    if(!output) {
        *output_len = 0;
        return E_POINTER;
    }

    if(!(*component) && source) {
        /* Allocate 'component', and copy the contents from 'source'
         * into the new allocation.
         */
        *component = heap_alloc((source_len+1)*sizeof(WCHAR));
        if(!(*component))
            return E_OUTOFMEMORY;

        memcpy(*component, source, source_len*sizeof(WCHAR));
        (*component)[source_len] = '\0';
        *component_len = source_len;
    }

    *output = *component;
    *output_len = *component_len;
    return *output ? S_OK : S_FALSE;
}