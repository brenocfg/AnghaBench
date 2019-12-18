#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {scalar_t__ num_rows; int /*<<< orphan*/ * storages; TYPE_1__* db; } ;
struct TYPE_4__ {int /*<<< orphan*/  storage; } ;
typedef  TYPE_2__ MSISTORAGESVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStorage_CopyTo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_CreateStorage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ MSI_RecordGetIStream (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STGM_WRITE ; 
 int /*<<< orphan*/  TRACE (char*,struct tagMSIVIEW*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_storage (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdupW (int /*<<< orphan*/ ) ; 
 scalar_t__ stream_to_storage (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static UINT STORAGES_set_row(struct tagMSIVIEW *view, UINT row, MSIRECORD *rec, UINT mask)
{
    MSISTORAGESVIEW *sv = (MSISTORAGESVIEW *)view;
    IStorage *stg, *substg = NULL;
    IStream *stm;
    LPWSTR name = NULL;
    HRESULT hr;
    UINT r = ERROR_FUNCTION_FAILED;

    TRACE("(%p, %p)\n", view, rec);

    if (row > sv->num_rows)
        return ERROR_FUNCTION_FAILED;

    r = MSI_RecordGetIStream(rec, 2, &stm);
    if (r != ERROR_SUCCESS)
        return r;

    r = stream_to_storage(stm, &stg);
    if (r != ERROR_SUCCESS)
    {
        IStream_Release(stm);
        return r;
    }

    name = strdupW(MSI_RecordGetString(rec, 1));
    if (!name)
    {
        r = ERROR_OUTOFMEMORY;
        goto done;
    }

    hr = IStorage_CreateStorage(sv->db->storage, name,
                                STGM_WRITE | STGM_SHARE_EXCLUSIVE,
                                0, 0, &substg);
    if (FAILED(hr))
    {
        r = ERROR_FUNCTION_FAILED;
        goto done;
    }

    hr = IStorage_CopyTo(stg, 0, NULL, NULL, substg);
    if (FAILED(hr))
    {
        r = ERROR_FUNCTION_FAILED;
        goto done;
    }

    sv->storages[row] = create_storage(sv, name, stg);
    if (!sv->storages[row])
        r = ERROR_FUNCTION_FAILED;

done:
    msi_free(name);

    if (substg) IStorage_Release(substg);
    IStorage_Release(stg);
    IStream_Release(stm);

    return r;
}