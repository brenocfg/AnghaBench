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
struct XRing {int tail; int head; scalar_t__* ring; } ;
typedef  scalar_t__ Element ;

/* Variables and functions */
 int XRING_SIZE ; 

__attribute__((used)) static Element
xring_remove(struct XRing *xring)
{
    volatile Element *ring = xring->ring;
    Element num;

    if (xring->tail >= xring->head)
        return 0;


    num = ring[xring->tail & (XRING_SIZE-1)];
    if (num) {
        ring[xring->tail & (XRING_SIZE-1)] = 0;
        xring->tail++;
        return num;
        /*
        int x = pixie_locked_CAS64(&ring[xring->tail & (XRING_SIZE-1)], 0, num);
        if (x) {
            xring->tail++;
            return num;
        } else {
            goto again;
        }*/
    } else {
        return 0;
    }
}