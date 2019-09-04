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
struct protocol {void* local; struct protocol* next; } ;
struct interface_info {int dummy; } ;

/* Variables and functions */
 struct protocol* protocols ; 

struct protocol *
find_protocol_by_adapter(struct interface_info *info)
{
    struct protocol *p;

    for( p = protocols; p; p = p->next ) {
        if( p->local == (void *)info ) return p;
    }

    return NULL;
}