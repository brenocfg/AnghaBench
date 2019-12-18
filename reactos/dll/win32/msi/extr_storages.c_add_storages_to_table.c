#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_14__ {int max_storages; TYPE_2__** storages; TYPE_1__* db; } ;
struct TYPE_13__ {scalar_t__ type; int /*<<< orphan*/  pwcsName; } ;
struct TYPE_12__ {int /*<<< orphan*/  storage; } ;
struct TYPE_11__ {int /*<<< orphan*/  storage; } ;
typedef  TYPE_2__ STORAGE ;
typedef  TYPE_3__ STATSTG ;
typedef  TYPE_4__ MSISTORAGESVIEW ;
typedef  int INT ;
typedef  int /*<<< orphan*/  IEnumSTATSTG ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEnumSTATSTG_Next (int /*<<< orphan*/ *,int,TYPE_3__*,int*) ; 
 int /*<<< orphan*/  IEnumSTATSTG_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_EnumElements (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_OpenStorage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int STGM_READ ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ STGTY_STORAGE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 TYPE_2__* create_storage (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 TYPE_2__** msi_alloc (int) ; 
 int /*<<< orphan*/  storages_set_table_size (TYPE_4__*,int) ; 

__attribute__((used)) static INT add_storages_to_table(MSISTORAGESVIEW *sv)
{
    STORAGE *storage = NULL;
    IEnumSTATSTG *stgenum = NULL;
    STATSTG stat;
    HRESULT hr;
    UINT count = 0, size;

    hr = IStorage_EnumElements(sv->db->storage, 0, NULL, 0, &stgenum);
    if (FAILED(hr))
        return -1;

    sv->max_storages = 1;
    sv->storages = msi_alloc(sizeof(STORAGE *));
    if (!sv->storages)
        return -1;

    while (TRUE)
    {
        size = 0;
        hr = IEnumSTATSTG_Next(stgenum, 1, &stat, &size);
        if (FAILED(hr) || !size)
            break;

        if (stat.type != STGTY_STORAGE)
        {
            CoTaskMemFree(stat.pwcsName);
            continue;
        }

        TRACE("enumerated storage %s\n", debugstr_w(stat.pwcsName));

        storage = create_storage(sv, stat.pwcsName, NULL);
        if (!storage)
        {
            count = -1;
            CoTaskMemFree(stat.pwcsName);
            break;
        }

        IStorage_OpenStorage(sv->db->storage, stat.pwcsName, NULL,
                             STGM_READ | STGM_SHARE_EXCLUSIVE, NULL, 0,
                             &storage->storage);
        CoTaskMemFree(stat.pwcsName);

        if (!storages_set_table_size(sv, ++count))
        {
            count = -1;
            break;
        }

        sv->storages[count - 1] = storage;
    }

    IEnumSTATSTG_Release(stgenum);
    return count;
}