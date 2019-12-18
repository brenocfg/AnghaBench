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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ nn_fast (int) ; 
 int nn_random_state ; 

void nn_random_generate (void *buf, size_t len)
{
    uint8_t *pos;

    pos = (uint8_t*) buf;

    while (1) {

        /*  Generate a pseudo-random integer. */
        nn_random_state = nn_random_state * 1103515245 + 12345;

        /*  Move the bytes to the output buffer. */
        memcpy (pos, &nn_random_state, len > 8 ? 8 : len);
        if (nn_fast (len <= 8))
            return;
        len -= 8;
        pos += 8;
    }
}