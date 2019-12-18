#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* HPDF_String ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_NameTree ;
typedef  scalar_t__ HPDF_INT32 ;
typedef  int /*<<< orphan*/  HPDF_Array ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Array_Add (int /*<<< orphan*/ ,void*) ; 
 void* HPDF_Array_GetItem (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Array_Insert (int /*<<< orphan*/ ,void*,void*) ; 
 scalar_t__ HPDF_Array_Items (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Dict_GetItem (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_INVALID_OBJECT ; 
 int /*<<< orphan*/  HPDF_INVALID_PARAMETER ; 
 int /*<<< orphan*/  HPDF_OCLASS_ARRAY ; 
 int /*<<< orphan*/  HPDF_OCLASS_STRING ; 
 int /*<<< orphan*/  HPDF_OK ; 
 scalar_t__ HPDF_String_Cmp (void*,void*) ; 

HPDF_STATUS
HPDF_NameTree_Add  (HPDF_NameTree  tree,
                    HPDF_String    name,
                    void          *obj)
{
    HPDF_Array items;
    HPDF_INT32 i, icount;

    if (!tree || !name)
        return HPDF_INVALID_PARAMETER;

    items = HPDF_Dict_GetItem (tree, "Names", HPDF_OCLASS_ARRAY);
    if (!items)
        return HPDF_INVALID_OBJECT;

    /* "The keys shall be sorted in lexical order" -- 7.9.6, Name Trees.
     * Since we store keys sorted, it's best to do a linear insertion sort
     * Find the first element larger than 'key', and insert 'key' and then
     * 'obj' into the items. */

    icount = HPDF_Array_Items(items);

    /* If we're larger than the last element, append */
    if (icount) {
        HPDF_String last = HPDF_Array_GetItem(items, icount - 2, HPDF_OCLASS_STRING);

        if (HPDF_String_Cmp(name, last) > 0) {
            HPDF_Array_Add(items, name);
            HPDF_Array_Add(items, obj);
            return HPDF_OK;
        }
    }

    /* Walk backwards through the list until we're smaller than an element=
     * That's the element to insert in front of. */
    for (i = icount - 4; i >= 0; i -= 2) {
        HPDF_String elem = HPDF_Array_GetItem(items, i, HPDF_OCLASS_STRING);

        if (i == 0 || HPDF_String_Cmp(name, elem) < 0) {
            HPDF_Array_Insert(items, elem, name);
            HPDF_Array_Insert(items, elem, obj);
            return HPDF_OK;
        }
    }

    /* Items list is empty */
    HPDF_Array_Add(items, name);
    HPDF_Array_Add(items, obj);
    return HPDF_OK;
}