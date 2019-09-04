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
struct XRing {scalar_t__ tail; scalar_t__ head; } ;
struct Test {int consumer_done; int /*<<< orphan*/  total_count; int /*<<< orphan*/  not_active; struct XRing* xring; } ;
typedef  scalar_t__ Element ;

/* Variables and functions */
 scalar_t__ xring_remove (struct XRing*) ; 

__attribute__((used)) static void
test_consumer_thread(void *v)
{
    struct Test *test = (struct Test *)v;
    struct XRing *xring = test->xring;


    while (!test->not_active) {
        Element e;

        e = xring_remove(xring);
        if (e == 0)
            ;
        else {
            test->total_count += e;
        }
    }

    while (xring->tail < xring->head) {
        Element e;

        e = xring_remove(xring);
        if (e == 0)
            ;
        else {
            test->total_count += e;
        }
    }

    test->consumer_done = 1;
}