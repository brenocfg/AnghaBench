#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ pszTemplate; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
struct TYPE_8__ {size_t nPages; TYPE_1__* proppage; } ;
struct TYPE_6__ {int /*<<< orphan*/  hpage; } ;
typedef  TYPE_3__ PropSheetInfo ;
typedef  scalar_t__ LRESULT ;
typedef  scalar_t__ LPVOID ;
typedef  TYPE_4__* LPCPROPSHEETPAGEA ;
typedef  size_t INT ;

/* Variables and functions */

__attribute__((used)) static INT PROPSHEET_FindPageByResId(const PropSheetInfo * psInfo, LRESULT resId)
{
   INT i;

   for (i = 0; i < psInfo->nPages; i++)
   {
      LPCPROPSHEETPAGEA lppsp = (LPCPROPSHEETPAGEA)psInfo->proppage[i].hpage;

      /* Fixme: if resource ID is a string shall we use strcmp ??? */
      if (lppsp->u.pszTemplate == (LPVOID)resId)
         break;
   }

   return i;
}