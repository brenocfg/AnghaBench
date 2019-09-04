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
typedef  int uint8_t ;

/* Variables and functions */
 int const* ELEM_DATA_MAX ; 
 int const ELEM_TYPE_END ; 

const uint8_t *elem_search(const uint8_t *elem, uint8_t elem_id) {
    while (elem + 2 + elem[1] <= ELEM_DATA_MAX) {
        if (elem[0] == elem_id) {
            // Found element, return a pointer to the element data
            return elem + 2;
        }
        if (elem[0] == ELEM_TYPE_END) {
            // End of elements
            return NULL;
        }
        elem += 2 + elem[1];
    }
    return NULL;
}