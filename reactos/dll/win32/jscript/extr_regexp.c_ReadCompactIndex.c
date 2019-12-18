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
typedef  int /*<<< orphan*/  jsbytecode ;

/* Variables and functions */

__attribute__((used)) static inline jsbytecode *
ReadCompactIndex(jsbytecode *pc, size_t *result)
{
    size_t nextByte;

    nextByte = *pc++;
    if ((nextByte & 0x80) == 0) {
        /*
         * Short-circuit the most common case when compact index <= 127.
         */
        *result = nextByte;
    } else {
        size_t shift = 7;
        *result = 0x7F & nextByte;
        do {
            nextByte = *pc++;
            *result |= (nextByte & 0x7F) << shift;
            shift += 7;
        } while ((nextByte & 0x80) != 0);
    }
    return pc;
}