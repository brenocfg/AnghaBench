#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ Magic; } ;
struct TYPE_14__ {TYPE_1__ OptionalHeader; } ;
struct TYPE_13__ {int /*<<< orphan*/  corhdr; int /*<<< orphan*/  data; TYPE_7__* nthdr; } ;
struct TYPE_12__ {int /*<<< orphan*/  VirtualAddress; int /*<<< orphan*/  Size; } ;
struct TYPE_11__ {TYPE_4__* DataDirectory; } ;
struct TYPE_10__ {TYPE_4__* DataDirectory; } ;
typedef  TYPE_2__ IMAGE_OPTIONAL_HEADER64 ;
typedef  TYPE_3__ IMAGE_OPTIONAL_HEADER32 ;
typedef  TYPE_4__ IMAGE_DATA_DIRECTORY ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_5__ ASSEMBLY ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 size_t IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR ; 
 scalar_t__ IMAGE_NT_OPTIONAL_HDR64_MAGIC ; 
 TYPE_7__* ImageNtHeader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ImageRvaToVa (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 

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

    if (!datadirs[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress ||
        !datadirs[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].Size)
    {
        return E_FAIL;
    }

    assembly->corhdr = ImageRvaToVa(assembly->nthdr, assembly->data,
        datadirs[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress, NULL);
    if (!assembly->corhdr)
        return E_FAIL;

    return S_OK;
}