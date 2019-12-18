#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* toc; } ;
struct TYPE_9__ {TYPE_2__* toc; } ;
struct TYPE_12__ {TYPE_5__ ds; TYPE_3__ jg; } ;
struct pdb_file_info {int kind; TYPE_6__ u; } ;
struct TYPE_10__ {int* file_size; } ;
struct TYPE_8__ {TYPE_1__* file; } ;
struct TYPE_7__ {int size; } ;
typedef  size_t DWORD ;

/* Variables and functions */
#define  PDB_DS 129 
#define  PDB_JG 128 

__attribute__((used)) static unsigned pdb_get_file_size(const struct pdb_file_info* pdb_file, DWORD file_nr)
{
    switch (pdb_file->kind)
    {
    case PDB_JG: return pdb_file->u.jg.toc->file[file_nr].size;
    case PDB_DS: return pdb_file->u.ds.toc->file_size[file_nr];
    }
    return 0;
}