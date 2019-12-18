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
typedef  int /*<<< orphan*/  COND_input ;

/* Variables and functions */
 void* cond_alloc (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 int /*<<< orphan*/  msi_free (void*) ; 

__attribute__((used)) static void *cond_track_mem( COND_input *cond, void *ptr, unsigned int sz )
{
    void *new_ptr;

    if( !ptr )
        return ptr;

    new_ptr = cond_alloc( cond, sz );
    if( !new_ptr )
    {
        msi_free( ptr );
        return NULL;
    }

    memcpy( new_ptr, ptr, sz );
    msi_free( ptr );
    return new_ptr;
}