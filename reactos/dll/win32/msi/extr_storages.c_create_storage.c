#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* db; } ;
struct TYPE_8__ {int /*<<< orphan*/ * storage; int /*<<< orphan*/  str_index; } ;
struct TYPE_7__ {int /*<<< orphan*/  strings; } ;
typedef  TYPE_2__ STORAGE ;
typedef  TYPE_3__ MSISTORAGESVIEW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IStorage ;

/* Variables and functions */
 int /*<<< orphan*/  IStorage_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StringNonPersistent ; 
 int /*<<< orphan*/  msi_add_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* msi_alloc (int) ; 

__attribute__((used)) static STORAGE *create_storage(MSISTORAGESVIEW *sv, LPCWSTR name, IStorage *stg)
{
    STORAGE *storage;

    storage = msi_alloc(sizeof(STORAGE));
    if (!storage)
        return NULL;

    storage->str_index = msi_add_string(sv->db->strings, name, -1, StringNonPersistent);
    storage->storage = stg;

    if (storage->storage)
        IStorage_AddRef(storage->storage);

    return storage;
}