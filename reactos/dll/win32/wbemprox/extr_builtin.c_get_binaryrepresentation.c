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
struct array {int count; int /*<<< orphan*/ * ptr; } ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  PSID ;

/* Variables and functions */
 void* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (struct array*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct array *get_binaryrepresentation( PSID sid, UINT len )
{
    struct array *array = heap_alloc( sizeof(struct array) );
    if (array)
    {
        UINT8 *ret = heap_alloc( len );
        if (ret)
        {
            memcpy( ret, sid, len );
            array->count = len;
            array->ptr = ret;
            return array;
        }
        heap_free( array );
    }
    return NULL;
}