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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  SearchItem ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStorage_OpenStorage (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STGM_READ ; 
 int /*<<< orphan*/ * SearchCHM_Storage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static SearchItem *SearchCHM_Folder(SearchItem *item, IStorage *pStorage,
                                    const WCHAR *folder, const char *needle)
{
    IStorage *temp_storage = NULL;
    HRESULT hres;

    hres = IStorage_OpenStorage(pStorage, folder, NULL, STGM_READ, NULL, 0, &temp_storage);
    if(FAILED(hres))
    {
        FIXME("Could not open '%s' storage object: %08x\n", debugstr_w(folder), hres);
        return NULL;
    }
    item = SearchCHM_Storage(item, temp_storage, needle);

    IStorage_Release(temp_storage);
    return item;
}