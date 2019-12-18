#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_10__ {char* pwcsName; int type; } ;
struct TYPE_9__ {struct TYPE_9__* next; } ;
typedef  TYPE_1__ SearchItem ;
typedef  TYPE_2__ STATSTG ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  IEnumSTATSTG ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,...) ; 
 scalar_t__ IEnumSTATSTG_Next (int /*<<< orphan*/ *,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumSTATSTG_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStorage_EnumElements (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ NOERROR ; 
#define  STGTY_STORAGE 129 
#define  STGTY_STREAM 128 
 scalar_t__ S_OK ; 
 char* SearchCHM_File (int /*<<< orphan*/ *,char*,char const*) ; 
 TYPE_1__* SearchCHM_Folder (TYPE_1__*,int /*<<< orphan*/ *,char*,char const*) ; 
 TYPE_1__* alloc_search_item (char*,char*) ; 
 char* wcschr (char*,char) ; 
 int /*<<< orphan*/  wcsstr (char*,char const*) ; 

__attribute__((used)) static SearchItem *SearchCHM_Storage(SearchItem *item, IStorage *pStorage,
                                     const char *needle)
{
    static const WCHAR szHTMext[] = {'.','h','t','m',0};
    IEnumSTATSTG *elem = NULL;
    WCHAR *filename = NULL;
    STATSTG entries;
    HRESULT hres;
    ULONG retr;

    hres = IStorage_EnumElements(pStorage, 0, NULL, 0, &elem);
    if(hres != S_OK)
    {
        FIXME("Could not enumerate '/' storage elements: %08x\n", hres);
        return NULL;
    }
    while (IEnumSTATSTG_Next(elem, 1, &entries, &retr) == NOERROR)
    {
        filename = entries.pwcsName;
        while(wcschr(filename, '/'))
            filename = wcschr(filename, '/')+1;
        switch(entries.type) {
        case STGTY_STORAGE:
            item = SearchCHM_Folder(item, pStorage, filename, needle);
            break;
        case STGTY_STREAM:
            if(wcsstr(filename, szHTMext))
            {
                WCHAR *title = SearchCHM_File(pStorage, filename, needle);

                if(title)
                {
                    item->next = alloc_search_item(title, entries.pwcsName);
                    item = item->next;
                }
            }
            break;
        default:
            FIXME("Unhandled IStorage stream element.\n");
        }
    }
    IEnumSTATSTG_Release(elem);
    return item;
}