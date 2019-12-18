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
struct XRing {int dummy; } ;
struct Test {int /*<<< orphan*/  producer_done; int /*<<< orphan*/  producer_started; struct XRing* xring; } ;

/* Variables and functions */
 scalar_t__ XringFailure ; 
 int /*<<< orphan*/  pixie_locked_add_u32 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ xring_add (struct XRing*,unsigned int) ; 

__attribute__((used)) static void
test_producer_thread(void *v)
{
    struct Test *test = (struct Test *)v;
    unsigned i = 1000;
    struct XRing *xring = test->xring;

    pixie_locked_add_u32(&test->producer_started, 1);
    while (i) {
        while (xring_add(xring, i) == XringFailure)
            ;
        i--;
    }
    pixie_locked_add_u32(&test->producer_done, 1);
}