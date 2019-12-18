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
struct Output {int /*<<< orphan*/ * src; } ;

/* Variables and functions */
 scalar_t__ is_myself (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static int
matches_me(struct Output *out, unsigned ip, unsigned port)
{
    unsigned i;

    for (i=0; i<8; i++) {
        if (is_myself(&out->src[i], ip, port))
            return 1;
    }
    return 0;
}