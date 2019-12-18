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
struct termbuf {unsigned int len; scalar_t__ mods; int /*<<< orphan*/ * b; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void skip_buf(struct termbuf *b, unsigned int count)
{
    assert(count <= b->len);

    memmove(&b->b[0], &b->b[count], b->len - count);
    b->len -= count;
    b->mods = 0;
}