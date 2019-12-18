#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inf_file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct ciffile {int ref; TYPE_1__ ICifFile_iface; int /*<<< orphan*/  groups; int /*<<< orphan*/  components; } ;
typedef  TYPE_1__ ICifFile ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICifFile_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ciffileVtbl ; 
 struct ciffile* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  inf_free (struct inf_file*) ; 
 int /*<<< orphan*/  inf_load (char const*,struct inf_file**) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_inf (struct ciffile*,struct inf_file*) ; 

__attribute__((used)) static HRESULT load_ciffile(const char *path, ICifFile **icif)
{
    struct inf_file *inf = NULL;
    struct ciffile *file;
    HRESULT hr = E_FAIL;

    file = heap_alloc_zero(sizeof(*file));
    if(!file) return E_OUTOFMEMORY;

    file->ICifFile_iface.lpVtbl = &ciffileVtbl;
    file->ref = 1;

    list_init(&file->components);
    list_init(&file->groups);

    hr = inf_load(path, &inf);
    if (FAILED(hr)) goto error;

    hr = process_inf(file, inf);
    if (FAILED(hr)) goto error;

    *icif = &file->ICifFile_iface;
    return S_OK;

error:
    if (inf) inf_free(inf);
    ICifFile_Release(&file->ICifFile_iface);
    return hr;
}