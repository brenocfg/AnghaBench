#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct image_section_map {size_t sidx; TYPE_3__* fmap; } ;
struct TYPE_6__ {size_t e_shnum; } ;
struct elf_file_map {char const* target_copy; TYPE_5__* sect; int /*<<< orphan*/  fd; TYPE_1__ elfhdr; } ;
struct TYPE_9__ {scalar_t__ sh_type; size_t sh_offset; size_t sh_size; } ;
struct TYPE_10__ {char const* mapped; TYPE_4__ shdr; } ;
struct TYPE_7__ {struct elf_file_map elf; } ;
struct TYPE_8__ {scalar_t__ modtype; TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ DMT_ELF ; 
 char const* IMAGE_NO_MAP ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  PROT_READ ; 
 scalar_t__ SHT_NOBITS ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 char const* mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t sysconf (int /*<<< orphan*/ ) ; 

const char* elf_map_section(struct image_section_map* ism)
{
    struct elf_file_map*        fmap = &ism->fmap->u.elf;
    size_t ofst, size, pgsz = sysconf( _SC_PAGESIZE );

    assert(ism->fmap->modtype == DMT_ELF);
    if (ism->sidx < 0 || ism->sidx >= ism->fmap->u.elf.elfhdr.e_shnum ||
        fmap->sect[ism->sidx].shdr.sh_type == SHT_NOBITS)
        return IMAGE_NO_MAP;

    if (fmap->target_copy)
    {
        return fmap->target_copy + fmap->sect[ism->sidx].shdr.sh_offset;
    }
    /* align required information on page size (we assume pagesize is a power of 2) */
    ofst = fmap->sect[ism->sidx].shdr.sh_offset & ~(pgsz - 1);
    size = ((fmap->sect[ism->sidx].shdr.sh_offset +
             fmap->sect[ism->sidx].shdr.sh_size + pgsz - 1) & ~(pgsz - 1)) - ofst;
    fmap->sect[ism->sidx].mapped = mmap(NULL, size, PROT_READ, MAP_PRIVATE,
                                        fmap->fd, ofst);
    if (fmap->sect[ism->sidx].mapped == IMAGE_NO_MAP) return IMAGE_NO_MAP;
    return fmap->sect[ism->sidx].mapped + (fmap->sect[ism->sidx].shdr.sh_offset & (pgsz - 1));
}