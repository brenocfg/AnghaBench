#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  szFile; } ;
struct TYPE_12__ {int /*<<< orphan*/  next; int /*<<< orphan*/  merge; scalar_t__ nItems; } ;
struct TYPE_9__ {int /*<<< orphan*/  pszIndex; } ;
struct TYPE_11__ {TYPE_5__* index; TYPE_2__* tabs; TYPE_8__* pCHMInfo; TYPE_1__ WinType; } ;
struct TYPE_10__ {int /*<<< orphan*/  hwnd; } ;
typedef  int /*<<< orphan*/  IndexItem ;
typedef  int /*<<< orphan*/  IStream ;
typedef  TYPE_3__ HHInfo ;

/* Variables and functions */
 int /*<<< orphan*/ * GetChmStream (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetChmPath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t TAB_INDEX ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  fill_index_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  parse_hhindex (TYPE_3__*,int /*<<< orphan*/ *,TYPE_5__*) ; 

void InitIndex(HHInfo *info)
{
    IStream *stream;

    info->index = heap_alloc_zero(sizeof(IndexItem));
    info->index->nItems = 0;
    SetChmPath(&info->index->merge, info->pCHMInfo->szFile, info->WinType.pszIndex);

    stream = GetChmStream(info->pCHMInfo, info->pCHMInfo->szFile, &info->index->merge);
    if(!stream) {
        TRACE("Could not get index stream\n");
        return;
    }

    parse_hhindex(info, stream, info->index);
    IStream_Release(stream);

    fill_index_tree(info->tabs[TAB_INDEX].hwnd, info->index->next);
}