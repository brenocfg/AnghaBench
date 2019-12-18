#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_8__ {size_t nText; int /*<<< orphan*/  entry; int /*<<< orphan*/  Text; int /*<<< orphan*/ * Blocks; int /*<<< orphan*/  Type; } ;
struct TYPE_7__ {int /*<<< orphan*/  Items; } ;
typedef  TYPE_1__ SYSLINK_INFO ;
typedef  int /*<<< orphan*/  SL_ITEM_TYPE ;
typedef  TYPE_2__* PDOC_ITEM ;
typedef  int /*<<< orphan*/ * LPCWSTR ;

/* Variables and functions */
 TYPE_2__* Alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DOC_ITEM ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_after (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 size_t min (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PDOC_ITEM SYSLINK_AppendDocItem (SYSLINK_INFO *infoPtr, LPCWSTR Text, UINT textlen,
                                        SL_ITEM_TYPE type, PDOC_ITEM LastItem)
{
    PDOC_ITEM Item;

    textlen = min(textlen, strlenW(Text));
    Item = Alloc(FIELD_OFFSET(DOC_ITEM, Text[textlen + 1]));
    if(Item == NULL)
    {
        ERR("Failed to alloc DOC_ITEM structure!\n");
        return NULL;
    }

    Item->nText = textlen;
    Item->Type = type;
    Item->Blocks = NULL;
    lstrcpynW(Item->Text, Text, textlen + 1);
    if (LastItem)
        list_add_after(&LastItem->entry, &Item->entry);
    else
        list_add_tail(&infoPtr->Items, &Item->entry);

    return Item;
}