#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ magic; int /*<<< orphan*/  (* destructor ) (TYPE_1__*) ;int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ MSIOBJECTHDR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int InterlockedDecrement (int /*<<< orphan*/ *) ; 
 scalar_t__ MSIHANDLE_MAGIC ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  msi_free (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

int msiobj_release( MSIOBJECTHDR *info )
{
    int ret;

    if( !info )
        return -1;

    if( info->magic != MSIHANDLE_MAGIC )
    {
        ERR("Invalid handle!\n");
        return -1;
    }

    ret = InterlockedDecrement( &info->refcount );
    if( ret==0 )
    {
        if( info->destructor )
            info->destructor( info );
        msi_free( info );
        TRACE("object %p destroyed\n", info);
    }

    return ret;
}