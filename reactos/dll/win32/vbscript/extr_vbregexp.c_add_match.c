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
struct TYPE_4__ {int size; int count; int /*<<< orphan*/ ** matches; } ;
typedef  TYPE_1__ MatchCollection2 ;
typedef  int /*<<< orphan*/  IMatchCollection2 ;
typedef  int /*<<< orphan*/  IMatch2 ;
typedef  int /*<<< orphan*/  IMatch ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IMatch2_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** heap_alloc (int) ; 
 int /*<<< orphan*/ ** heap_realloc (int /*<<< orphan*/ **,int) ; 
 TYPE_1__* impl_from_IMatchCollection2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT add_match(IMatchCollection2 *iface, IMatch2 *add)
{
    MatchCollection2 *This = impl_from_IMatchCollection2(iface);

    TRACE("(%p)->(%p)\n", This, add);

    if(!This->size) {
        This->matches = heap_alloc(8*sizeof(IMatch*));
        if(!This->matches)
            return E_OUTOFMEMORY;
        This->size = 8;
    }else if(This->size == This->count) {
        IMatch2 **new_matches = heap_realloc(This->matches, 2*This->size*sizeof(IMatch*));
        if(!new_matches)
            return E_OUTOFMEMORY;

        This->matches = new_matches;
        This->size <<= 1;
    }

    This->matches[This->count++] = add;
    IMatch2_AddRef(add);
    return S_OK;
}