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
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t NumberOfSections; } ;
struct TYPE_10__ {TYPE_2__ FileHeader; } ;
struct pe_file_map {TYPE_6__* sect; TYPE_3__ ntheader; } ;
struct image_section_map {size_t sidx; TYPE_7__* fmap; } ;
struct TYPE_8__ {struct pe_file_map pe; } ;
struct TYPE_14__ {TYPE_1__ u; } ;
struct TYPE_11__ {scalar_t__ VirtualSize; } ;
struct TYPE_12__ {scalar_t__ SizeOfRawData; int /*<<< orphan*/  VirtualAddress; TYPE_4__ Misc; } ;
struct TYPE_13__ {scalar_t__ mapped; TYPE_5__ shdr; } ;
typedef  int /*<<< orphan*/  IMAGE_NT_HEADERS ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,size_t,scalar_t__,scalar_t__) ; 
 scalar_t__ IMAGE_NO_MAP ; 
 scalar_t__ RtlImageRvaToVa (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* pe_map_full (TYPE_7__*,int /*<<< orphan*/ **) ; 

const char* pe_map_section(struct image_section_map* ism)
{
    void*       mapping;
    struct pe_file_map* fmap = &ism->fmap->u.pe;

    if (ism->sidx >= 0 && ism->sidx < fmap->ntheader.FileHeader.NumberOfSections &&
        fmap->sect[ism->sidx].mapped == IMAGE_NO_MAP)
    {
        IMAGE_NT_HEADERS*       nth;

        if (fmap->sect[ism->sidx].shdr.Misc.VirtualSize > fmap->sect[ism->sidx].shdr.SizeOfRawData)
        {
            FIXME("Section %ld: virtual (0x%x) > raw (0x%x) size - not supported\n",
                  ism->sidx, fmap->sect[ism->sidx].shdr.Misc.VirtualSize,
                  fmap->sect[ism->sidx].shdr.SizeOfRawData);
            return IMAGE_NO_MAP;
        }
        /* FIXME: that's rather drastic, but that will do for now
         * that's ok if the full file map exists, but we could be less aggressive otherwise and
         * only map the relevant section
         */
        if ((mapping = pe_map_full(ism->fmap, &nth)))
        {
            fmap->sect[ism->sidx].mapped = RtlImageRvaToVa(nth, mapping,
                                                           fmap->sect[ism->sidx].shdr.VirtualAddress,
                                                           NULL);
            return fmap->sect[ism->sidx].mapped;
        }
    }
    return IMAGE_NO_MAP;
}