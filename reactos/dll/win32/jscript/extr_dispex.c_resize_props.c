#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int buf_size; int prop_cnt; TYPE_2__* props; } ;
typedef  TYPE_1__ jsdisp_t ;
struct TYPE_8__ {int bucket_head; int bucket_next; int /*<<< orphan*/  hash; } ;
typedef  TYPE_2__ dispex_prop_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int get_props_idx (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* heap_realloc (TYPE_2__*,int) ; 

__attribute__((used)) static inline HRESULT resize_props(jsdisp_t *This)
{
    dispex_prop_t *props;
    int i, bucket;

    if(This->buf_size != This->prop_cnt)
        return S_FALSE;

    props = heap_realloc(This->props, sizeof(dispex_prop_t)*This->buf_size*2);
    if(!props)
        return E_OUTOFMEMORY;
    This->buf_size *= 2;
    This->props = props;

    for(i=0; i<This->buf_size; i++) {
        This->props[i].bucket_head = 0;
        This->props[i].bucket_next = 0;
    }

    for(i=1; i<This->prop_cnt; i++) {
        props = This->props+i;

        bucket = get_props_idx(This, props->hash);
        props->bucket_next = This->props[bucket].bucket_head;
        This->props[bucket].bucket_head = i;
    }

    return S_OK;
}