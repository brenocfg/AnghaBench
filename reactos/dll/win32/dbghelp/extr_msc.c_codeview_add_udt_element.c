#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int type; int nbits; int /*<<< orphan*/  bitoff; } ;
struct TYPE_5__ {unsigned int type; int nbits; int /*<<< orphan*/  bitoff; } ;
struct TYPE_4__ {int id; } ;
union codeview_reftype {TYPE_3__ bitfield_v2; TYPE_2__ bitfield_v1; TYPE_1__ generic; } ;
struct symt_udt {int dummy; } ;
struct symt {int dummy; } ;
struct codeview_type_parse {int /*<<< orphan*/  module; } ;
typedef  scalar_t__ DWORD64 ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  LF_BITFIELD_V1 129 
#define  LF_BITFIELD_V2 128 
 int /*<<< orphan*/  TI_GET_LENGTH ; 
 struct symt* codeview_fetch_type (struct codeview_type_parse*,unsigned int,int /*<<< orphan*/ ) ; 
 union codeview_reftype* codeview_jump_to_type (struct codeview_type_parse*,unsigned int) ; 
 int /*<<< orphan*/  symt_add_udt_element (int /*<<< orphan*/ ,struct symt_udt*,char const*,struct symt*,int,int) ; 
 int /*<<< orphan*/  symt_get_info (int /*<<< orphan*/ ,struct symt*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void codeview_add_udt_element(struct codeview_type_parse* ctp,
                                     struct symt_udt* symt, const char* name,
                                     int value, unsigned type)
{
    struct symt*                subtype;
    const union codeview_reftype*cv_type;

    if ((cv_type = codeview_jump_to_type(ctp, type)))
    {
        switch (cv_type->generic.id)
        {
        case LF_BITFIELD_V1:
            symt_add_udt_element(ctp->module, symt, name,
                                 codeview_fetch_type(ctp, cv_type->bitfield_v1.type, FALSE),
                                 (value << 3) + cv_type->bitfield_v1.bitoff,
                                 cv_type->bitfield_v1.nbits);
            return;
        case LF_BITFIELD_V2:
            symt_add_udt_element(ctp->module, symt, name,
                                 codeview_fetch_type(ctp, cv_type->bitfield_v2.type, FALSE),
                                 (value << 3) + cv_type->bitfield_v2.bitoff,
                                 cv_type->bitfield_v2.nbits);
            return;
        }
    }
    subtype = codeview_fetch_type(ctp, type, FALSE);

    if (subtype)
    {
        DWORD64 elem_size = 0;
        symt_get_info(ctp->module, subtype, TI_GET_LENGTH, &elem_size);
        symt_add_udt_element(ctp->module, symt, name, subtype,
                             value << 3, (DWORD)elem_size << 3);
    }
}