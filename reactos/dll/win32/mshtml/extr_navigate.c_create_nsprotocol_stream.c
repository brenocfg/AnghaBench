#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; scalar_t__ buf_size; TYPE_1__ nsIInputStream_iface; } ;
typedef  TYPE_2__ nsProtocolStream ;

/* Variables and functions */
 TYPE_2__* heap_alloc (int) ; 
 int /*<<< orphan*/  nsInputStreamVtbl ; 

__attribute__((used)) static nsProtocolStream *create_nsprotocol_stream(void)
{
    nsProtocolStream *ret;

    ret = heap_alloc(sizeof(nsProtocolStream));
    if(!ret)
        return NULL;

    ret->nsIInputStream_iface.lpVtbl = &nsInputStreamVtbl;
    ret->ref = 1;
    ret->buf_size = 0;

    return ret;
}