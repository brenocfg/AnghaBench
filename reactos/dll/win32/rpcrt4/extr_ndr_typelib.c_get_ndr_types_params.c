#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned char* ProcFormatString; int* FormatStringOffset; } ;
struct TYPE_10__ {int Oi_flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  Size; } ;
struct TYPE_7__ {scalar_t__ HasExtensions; } ;
struct TYPE_8__ {unsigned int number_of_params; TYPE_1__ Oi2Flags; } ;
typedef  TYPE_2__ NDR_PROC_PARTIAL_OIF_HEADER ;
typedef  int /*<<< orphan*/  NDR_PROC_HEADER_RPC ;
typedef  TYPE_3__ NDR_PROC_HEADER_EXTS ;
typedef  TYPE_4__ NDR_PROC_HEADER ;
typedef  int /*<<< orphan*/  NDR_PARAM_OIF ;
typedef  TYPE_5__ MIDL_STUBLESS_PROXY_INFO ;

/* Variables and functions */
 int Oi_HAS_RPCFLAGS ; 
 TYPE_5__* get_ndr_types_proxy_info () ; 

__attribute__((used)) static const NDR_PARAM_OIF *get_ndr_types_params( unsigned int *nb_params )
{
    const MIDL_STUBLESS_PROXY_INFO *proxy = get_ndr_types_proxy_info();
    const unsigned char *format = proxy->ProcFormatString + proxy->FormatStringOffset[3];
    const NDR_PROC_HEADER *proc = (const NDR_PROC_HEADER *)format;
    const NDR_PROC_PARTIAL_OIF_HEADER *header;

    if (proc->Oi_flags & Oi_HAS_RPCFLAGS)
        format += sizeof(NDR_PROC_HEADER_RPC);
    else
        format += sizeof(NDR_PROC_HEADER);

    header = (const NDR_PROC_PARTIAL_OIF_HEADER *)format;
    format += sizeof(*header);
    if (header->Oi2Flags.HasExtensions)
    {
        const NDR_PROC_HEADER_EXTS *ext = (const NDR_PROC_HEADER_EXTS *)format;
        format += ext->Size;
    }
    *nb_params = header->number_of_params;
    return (const NDR_PARAM_OIF *)format;
}