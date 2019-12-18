#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {TYPE_1__* obj; } ;
struct TYPE_6__ {TYPE_2__ u; scalar_t__ remote; } ;
struct TYPE_4__ {scalar_t__ magic; scalar_t__ type; } ;
typedef  void MSIOBJECTHDR ;
typedef  size_t MSIHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ MSIHANDLE_MAGIC ; 
 int /*<<< orphan*/  MSI_handle_cs ; 
 TYPE_3__* msihandletable ; 
 size_t msihandletable_size ; 
 int /*<<< orphan*/  msiobj_addref (void*) ; 

void *msihandle2msiinfo(MSIHANDLE handle, UINT type)
{
    MSIOBJECTHDR *ret = NULL;

    EnterCriticalSection( &MSI_handle_cs );
    handle--;
    if( handle >= msihandletable_size )
        goto out;
    if( msihandletable[handle].remote)
        goto out;
    if( !msihandletable[handle].u.obj )
        goto out;
    if( msihandletable[handle].u.obj->magic != MSIHANDLE_MAGIC )
        goto out;
    if( type && (msihandletable[handle].u.obj->type != type) )
        goto out;
    ret = msihandletable[handle].u.obj;
    msiobj_addref( ret );

out:
    LeaveCriticalSection( &MSI_handle_cs );

    return ret;
}