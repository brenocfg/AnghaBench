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
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;
struct TYPE_6__ {TYPE_1__ elf; } ;
struct image_file_map {TYPE_2__ u; } ;
struct TYPE_7__ {scalar_t__ load_addr; int /*<<< orphan*/  handle; } ;
struct TYPE_8__ {TYPE_3__ process; } ;
struct elf_map_file_data {int kind; TYPE_4__ u; } ;
typedef  scalar_t__ off_t ;
typedef  size_t SIZE_T ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  ReadProcessMemory (int /*<<< orphan*/ ,void*,void*,size_t,size_t*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
#define  from_file 129 
#define  from_process 128 
 size_t pread (int /*<<< orphan*/ ,void*,size_t,scalar_t__) ; 

__attribute__((used)) static BOOL elf_map_file_read(struct image_file_map* fmap, struct elf_map_file_data* emfd,
                              void* buf, size_t len, off_t off)
{
    SIZE_T dw;

    switch (emfd->kind)
    {
    case from_file:
        return pread(fmap->u.elf.fd, buf, len, off) == len;
    case from_process:
        return ReadProcessMemory(emfd->u.process.handle,
                                 (void*)((unsigned long)emfd->u.process.load_addr + (unsigned long)off),
                                 buf, len, &dw) && dw == len;
    default:
        assert(0);
        return FALSE;
    }
}