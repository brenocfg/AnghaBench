#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct image_section_map {int dummy; } ;
struct image_file_map {int dummy; } ;
struct TYPE_4__ {scalar_t__ rva; scalar_t__ size; int /*<<< orphan*/  const* address; int /*<<< orphan*/  compressed; } ;
typedef  TYPE_1__ dwarf2_section_t ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dwarf2_init_zsection (TYPE_1__*,char const*,struct image_section_map*) ; 
 scalar_t__ image_find_section (struct image_file_map*,char const*,struct image_section_map*) ; 
 scalar_t__ image_get_map_rva (struct image_section_map*) ; 
 scalar_t__ image_get_map_size (struct image_section_map*) ; 
 scalar_t__ image_map_section (struct image_section_map*) ; 

__attribute__((used)) static inline BOOL dwarf2_init_section(dwarf2_section_t* section, struct image_file_map* fmap,
                                       const char* sectname, const char* zsectname,
                                       struct image_section_map* ism)
{
    struct image_section_map    local_ism;

    if (!ism) ism = &local_ism;

    section->compressed = FALSE;
    if (image_find_section(fmap, sectname, ism))
    {
        section->address = (const BYTE*)image_map_section(ism);
        section->size    = image_get_map_size(ism);
        section->rva     = image_get_map_rva(ism);
        return TRUE;
    }

    section->address = NULL;
    section->size    = 0;
    section->rva     = 0;

    if (zsectname && image_find_section(fmap, zsectname, ism))
    {
#ifdef HAVE_ZLIB
        return dwarf2_init_zsection(section, zsectname, ism);
#else
        FIXME("dbghelp not built with zlib, but compressed section found\n" );
#endif
    }

    return FALSE;
}