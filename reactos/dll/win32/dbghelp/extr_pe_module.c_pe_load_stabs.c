#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct process {int dummy; } ;
struct TYPE_12__ {scalar_t__ BaseOfImage; } ;
struct module {TYPE_4__ module; TYPE_3__** format_info; } ;
struct image_section_map {int dummy; } ;
struct TYPE_13__ {scalar_t__ ImageBase; } ;
struct TYPE_14__ {TYPE_5__ OptionalHeader; } ;
struct TYPE_15__ {TYPE_6__ ntheader; } ;
struct TYPE_16__ {TYPE_7__ pe; } ;
struct image_file_map {TYPE_8__ u; } ;
struct TYPE_10__ {TYPE_1__* pe_info; } ;
struct TYPE_11__ {TYPE_2__ u; } ;
struct TYPE_9__ {struct image_file_map fmap; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t DFI_PE ; 
 scalar_t__ FALSE ; 
 char const* IMAGE_NO_MAP ; 
 int /*<<< orphan*/  TRACE (char*,char*) ; 
 int /*<<< orphan*/  image_get_map_size (struct image_section_map*) ; 
 char* image_map_section (struct image_section_map*) ; 
 int /*<<< orphan*/  image_unmap_section (struct image_section_map*) ; 
 scalar_t__ pe_find_section (struct image_file_map*,char*,struct image_section_map*) ; 
 int /*<<< orphan*/  pe_locate_with_coff_symbol_table (struct module*) ; 
 scalar_t__ stabs_parse (struct module*,scalar_t__,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL pe_load_stabs(const struct process* pcs, struct module* module)
{
    struct image_file_map*      fmap = &module->format_info[DFI_PE]->u.pe_info->fmap;
    struct image_section_map    sect_stabs, sect_stabstr;
    BOOL                        ret = FALSE;

    if (pe_find_section(fmap, ".stab", &sect_stabs) && pe_find_section(fmap, ".stabstr", &sect_stabstr))
    {
        const char* stab;
        const char* stabstr;

        stab = image_map_section(&sect_stabs);
        stabstr = image_map_section(&sect_stabstr);
        if (stab != IMAGE_NO_MAP && stabstr != IMAGE_NO_MAP)
        {
            ret = stabs_parse(module,
                              module->module.BaseOfImage - fmap->u.pe.ntheader.OptionalHeader.ImageBase,
                              stab, image_get_map_size(&sect_stabs),
                              stabstr, image_get_map_size(&sect_stabstr),
                              NULL, NULL);
        }
        image_unmap_section(&sect_stabs);
        image_unmap_section(&sect_stabstr);
        if (ret) pe_locate_with_coff_symbol_table(module);
    }
    TRACE("%s the STABS debug info\n", ret ? "successfully loaded" : "failed to load");

    return ret;
}