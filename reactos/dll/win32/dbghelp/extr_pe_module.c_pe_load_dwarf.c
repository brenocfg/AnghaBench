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
struct TYPE_12__ {scalar_t__ BaseOfImage; } ;
struct module {TYPE_4__ module; TYPE_3__** format_info; } ;
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
 int /*<<< orphan*/  TRACE (char*,char*) ; 
 scalar_t__ dwarf2_parse (struct module*,scalar_t__,int /*<<< orphan*/ *,struct image_file_map*) ; 

__attribute__((used)) static BOOL pe_load_dwarf(struct module* module)
{
    struct image_file_map*      fmap = &module->format_info[DFI_PE]->u.pe_info->fmap;
    BOOL                        ret;

    ret = dwarf2_parse(module,
                       module->module.BaseOfImage - fmap->u.pe.ntheader.OptionalHeader.ImageBase,
                       NULL, /* FIXME: some thunks to deal with ? */
                       fmap);
    TRACE("%s the DWARF debug info\n", ret ? "successfully loaded" : "failed to load");

    return ret;
}