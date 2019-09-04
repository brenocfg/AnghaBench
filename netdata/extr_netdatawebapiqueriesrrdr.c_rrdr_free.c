#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* od; struct TYPE_5__* o; struct TYPE_5__* v; struct TYPE_5__* t; } ;
typedef  TYPE_1__ RRDR ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  freez (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdr_unlock_rrdset (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

inline void rrdr_free(RRDR *r)
{
    if(unlikely(!r)) {
        error("NULL value given!");
        return;
    }

    rrdr_unlock_rrdset(r);
    freez(r->t);
    freez(r->v);
    freez(r->o);
    freez(r->od);
    freez(r);
}