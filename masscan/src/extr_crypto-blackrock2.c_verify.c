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
typedef  scalar_t__ uint64_t ;
struct BlackRock {scalar_t__ range; } ;

/* Variables and functions */
 unsigned char* CALLOC (int,size_t) ; 
 scalar_t__ blackrock2_shuffle (struct BlackRock*,scalar_t__) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 

__attribute__((used)) static unsigned
verify(struct BlackRock *br, uint64_t max)
{
    unsigned char *list;
    uint64_t i;
    unsigned is_success = 1;
    uint64_t range = br->range;

    /* Allocate a list of 1-byte counters */
    list = CALLOC(1, (size_t)((range<max)?range:max));
    
    /* For all numbers in the range, verify increment the counter for the
     * the output. */
    for (i=0; i<range; i++) {
        uint64_t x = blackrock2_shuffle(br, i);
        if (x < max)
            list[x]++;
    }

    /* Now check the output to make sure that every counter is set exactly
     * to the value of '1'. */
    for (i=0; i<max && i<range; i++) {
        if (list[i] != 1)
            is_success = 0;
    }

    free(list);

    return is_success;
}