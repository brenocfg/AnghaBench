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
struct BlackRock {scalar_t__ range; int /*<<< orphan*/  seed; int /*<<< orphan*/  b; int /*<<< orphan*/  a; int /*<<< orphan*/  rounds; } ;

/* Variables and functions */
 scalar_t__ DECRYPT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

uint64_t
blackrock2_unshuffle(const struct BlackRock *br, uint64_t m)
{
    uint64_t c;

    c = DECRYPT(br->rounds, br->a, br->b, m, br->seed);
    while (c >= br->range)
        c = DECRYPT(br->rounds, br->a, br->b,  c, br->seed);

    return c;
}