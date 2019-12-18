#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {TYPE_3__* szUrl; TYPE_3__* szID; } ;
struct TYPE_7__ {TYPE_1__ Link; } ;
struct TYPE_8__ {scalar_t__ Type; struct TYPE_8__* Blocks; TYPE_2__ u; } ;
typedef  TYPE_3__* PDOC_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_3__*) ; 
 scalar_t__ slLink ; 

__attribute__((used)) static VOID SYSLINK_FreeDocItem (PDOC_ITEM DocItem)
{
    if(DocItem->Type == slLink)
    {
        Free(DocItem->u.Link.szID);
        Free(DocItem->u.Link.szUrl);
    }

    Free(DocItem->Blocks);

    /* we don't free Text because it's just a pointer to a character in the
       entire window text string */

    Free(DocItem);
}