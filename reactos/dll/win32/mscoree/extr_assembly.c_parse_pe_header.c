#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ Magic; } ;
struct TYPE_12__ {TYPE_1__ OptionalHeader; } ;
struct TYPE_11__ {int /*<<< orphan*/  corhdr; TYPE_7__* nthdr; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int /*<<< orphan*/ * DataDirectory; } ;
struct TYPE_9__ {int /*<<< orphan*/ * DataDirectory; } ;
typedef  TYPE_2__ IMAGE_OPTIONAL_HEADER64 ;
typedef  TYPE_3__ IMAGE_OPTIONAL_HEADER32 ;
typedef  int /*<<< orphan*/  IMAGE_DATA_DIRECTORY ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_4__ ASSEMBLY ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 size_t IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR ; 
 scalar_t__ IMAGE_NT_OPTIONAL_HDR64_MAGIC ; 
 TYPE_7__* ImageNtHeader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  assembly_datadir_get_data (TYPE_4__*,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static HRESULT parse_pe_header(ASSEMBLY *assembly)
{
    IMAGE_DATA_DIRECTORY *datadirs;

    assembly->nthdr = ImageNtHeader(assembly->data);
    if (!assembly->nthdr)
        return E_FAIL;

    if (assembly->nthdr->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
    {
        IMAGE_OPTIONAL_HEADER64 *opthdr =
                (IMAGE_OPTIONAL_HEADER64 *)&assembly->nthdr->OptionalHeader;
        datadirs = opthdr->DataDirectory;
    }
    else
    {
        IMAGE_OPTIONAL_HEADER32 *opthdr =
                (IMAGE_OPTIONAL_HEADER32 *)&assembly->nthdr->OptionalHeader;
        datadirs = opthdr->DataDirectory;
    }

    if (!datadirs)
        return E_FAIL;

    if (!assembly_datadir_get_data(assembly, &datadirs[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR], (void**)&assembly->corhdr))
        return E_FAIL;

    return S_OK;
}