#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  attr; } ;
struct TYPE_9__ {int /*<<< orphan*/ * tag; } ;
struct TYPE_7__ {scalar_t__ num_tables; TYPE_3__* table; } ;
struct TYPE_8__ {TYPE_1__ offset_tbl; } ;
typedef  scalar_t__ HPDF_UINT ;
typedef  TYPE_2__* HPDF_TTFontDefAttr ;
typedef  TYPE_3__ HPDF_TTFTable ;
typedef  TYPE_4__* HPDF_FontDef ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 scalar_t__ HPDF_MemCmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

__attribute__((used)) static HPDF_TTFTable*
FindTable (HPDF_FontDef      fontdef,
           const char  *tag)
{
    HPDF_TTFontDefAttr attr = (HPDF_TTFontDefAttr)fontdef->attr;
    HPDF_TTFTable* tbl = attr->offset_tbl.table;
    HPDF_UINT i;

    for (i = 0; i < attr->offset_tbl.num_tables; i++, tbl++) {
        if (HPDF_MemCmp ((HPDF_BYTE *)tbl->tag, (HPDF_BYTE *)tag, 4) == 0) {
            HPDF_PTRACE((" FindTable find table[%c%c%c%c]\n",
                        tbl->tag[0], tbl->tag[1], tbl->tag[2], tbl->tag[3]));
            return tbl;
        }
    }

    return NULL;
}