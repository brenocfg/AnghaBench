#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type_offset; int /*<<< orphan*/  file; int /*<<< orphan*/  last_index; int /*<<< orphan*/  first_index; int /*<<< orphan*/  type_size; int /*<<< orphan*/  version; } ;
struct TYPE_5__ {int /*<<< orphan*/  file; int /*<<< orphan*/  last_index; int /*<<< orphan*/  first_index; int /*<<< orphan*/  type_size; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ PDB_TYPES_OLD ;
typedef  TYPE_2__ PDB_TYPES ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pdb_convert_types_header(PDB_TYPES* types, const BYTE* image)
{
    memset(types, 0, sizeof(PDB_TYPES));
    if (!image) return;

    if (*(const DWORD*)image < 19960000)   /* FIXME: correct version? */
    {
        /* Old version of the types record header */
        const PDB_TYPES_OLD*    old = (const PDB_TYPES_OLD*)image;
        types->version     = old->version;
        types->type_offset = sizeof(PDB_TYPES_OLD);
        types->type_size   = old->type_size;
        types->first_index = old->first_index;
        types->last_index  = old->last_index;
        types->file        = old->file;
    }
    else
    {
        /* New version of the types record header */
        *types = *(const PDB_TYPES*)image;
    }
}