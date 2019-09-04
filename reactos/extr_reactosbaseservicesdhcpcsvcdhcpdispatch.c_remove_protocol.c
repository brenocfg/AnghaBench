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
struct timeout {struct timeout* next; struct interface_info* what; } ;
struct protocol {struct protocol* next; struct interface_info* local; } ;
struct interface_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct protocol*) ; 
 struct timeout* free_timeouts ; 
 struct protocol* protocols ; 
 struct timeout* timeouts ; 

void
remove_protocol(struct protocol *proto)
{
    struct protocol *p, *next, *prev;
    struct interface_info *ip = proto->local;
    struct timeout *t, *q, *u;
    
    t = NULL;
    q = timeouts;
    while (q != NULL)
    {
        /* Remove all timeouts for this protocol */
        if (q->what == ip)
        {
            /* Unlink the timeout from previous */
            if (t)
                t->next = q->next;
            else
                timeouts = q->next;
                        
            /* Advance to the next timeout */
            u = q->next;
            
            /* Add it to the free list */
            q->next = free_timeouts;
            free_timeouts = q;
        }
        else
        {
            /* Advance to the next timeout */
            u = q->next;
            
            /* Update the previous pointer */
            t = q;
        }
        
        /* Advance */
        q = u;
    }

    prev = NULL;
    for (p = protocols; p; p = next) {
        next = p->next;
        if (p == proto) {
            if (prev)
                prev->next = p->next;
            else
                protocols = p->next;
            free(p);
        }
    }
}