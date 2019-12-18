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
struct XRing {scalar_t__* ring; int head; int tail; } ;
typedef  scalar_t__ Element ;

/* Variables and functions */
 int XRING_SIZE ; 
 int XringFailure ; 
 int XringSuccess ; 

__attribute__((used)) static int
xring_add(struct XRing *xring, Element value)
{
    volatile Element *ring = xring->ring;
    Element num;

    if (value == 0) {
        return XringFailure;
    }

    if (xring->head >= xring->tail + XRING_SIZE) {
        //printf("-");
        return XringFailure;
    }
    num = xring->ring[xring->head & (XRING_SIZE-1)];
    if (num == 0) {
        ring[xring->head & (XRING_SIZE-1)] = value;
        xring->head++;
        return XringSuccess;
        /*int x = pixie_locked_CAS64(&ring[xring->head & (XRING_SIZE-1)], value, 0);
        if (x) {
            xring->head++;
            return XringSuccess;
        } else {
            return XringFailure;
        }*/
    }
    return XringFailure;
}