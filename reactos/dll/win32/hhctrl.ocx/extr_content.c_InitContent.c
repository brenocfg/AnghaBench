#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  insert_type_t ;
struct TYPE_15__ {int /*<<< orphan*/  child; int /*<<< orphan*/  merge; } ;
struct TYPE_12__ {int /*<<< orphan*/  pszToc; } ;
struct TYPE_14__ {TYPE_4__* content; TYPE_2__* tabs; TYPE_10__* pCHMInfo; TYPE_1__ WinType; } ;
struct TYPE_13__ {int /*<<< orphan*/  hwnd; } ;
struct TYPE_11__ {int /*<<< orphan*/  szFile; } ;
typedef  int /*<<< orphan*/  IStream ;
typedef  TYPE_3__ HHInfo ;
typedef  int /*<<< orphan*/  ContentItem ;

/* Variables and functions */
 int /*<<< orphan*/ * GetChmStream (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetChmPath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t TAB_CONTENTS ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  fill_content_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_4__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  parse_hhc (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_item_parents (int /*<<< orphan*/ *,TYPE_4__*) ; 

void InitContent(HHInfo *info)
{
    IStream *stream;
    insert_type_t insert_type;

    info->content = heap_alloc_zero(sizeof(ContentItem));
    SetChmPath(&info->content->merge, info->pCHMInfo->szFile, info->WinType.pszToc);

    stream = GetChmStream(info->pCHMInfo, info->pCHMInfo->szFile, &info->content->merge);
    if(!stream) {
        TRACE("Could not get content stream\n");
        return;
    }

    info->content->child = parse_hhc(info, stream, info->content, &insert_type);
    IStream_Release(stream);

    set_item_parents(NULL, info->content);
    fill_content_tree(info->tabs[TAB_CONTENTS].hwnd, NULL, info->content);
}