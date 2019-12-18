#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct image_section_map {scalar_t__ sidx; struct image_file_map* fmap; } ;
struct TYPE_5__ {scalar_t__ NumberOfSections; } ;
struct TYPE_6__ {TYPE_1__ FileHeader; } ;
struct TYPE_7__ {void* sect; int /*<<< orphan*/ * hMap; scalar_t__ strtable; scalar_t__ full_count; TYPE_2__ ntheader; } ;
struct TYPE_8__ {TYPE_3__ pe; } ;
struct image_file_map {TYPE_4__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pe_unmap_full (struct image_file_map*) ; 
 int /*<<< orphan*/  pe_unmap_section (struct image_section_map*) ; 

__attribute__((used)) static void pe_unmap_file(struct image_file_map* fmap)
{
    if (fmap->u.pe.hMap != 0)
    {
        struct image_section_map  ism;
        ism.fmap = fmap;
        for (ism.sidx = 0; ism.sidx < fmap->u.pe.ntheader.FileHeader.NumberOfSections; ism.sidx++)
        {
            pe_unmap_section(&ism);
        }
        while (fmap->u.pe.full_count) pe_unmap_full(fmap);
        HeapFree(GetProcessHeap(), 0, fmap->u.pe.sect);
        HeapFree(GetProcessHeap(), 0, (void*)fmap->u.pe.strtable); /* FIXME ugly (see pe_map_file) */
        CloseHandle(fmap->u.pe.hMap);
        fmap->u.pe.hMap = NULL;
    }
}