#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ ** data; } ;
typedef  TYPE_1__ IDEA_KEY_SCHEDULE ;
typedef  int /*<<< orphan*/  IDEA_INT ;

/* Variables and functions */
 int /*<<< orphan*/  E_IDEA (int) ; 
 int /*<<< orphan*/  idea_mul (unsigned long,unsigned long,int /*<<< orphan*/ ,unsigned long) ; 

void IDEA_encrypt(unsigned long *d, IDEA_KEY_SCHEDULE *key)
{
    register IDEA_INT *p;
    register unsigned long x1, x2, x3, x4, t0, t1, ul;

    x2 = d[0];
    x1 = (x2 >> 16);
    x4 = d[1];
    x3 = (x4 >> 16);

    p = &(key->data[0][0]);

    E_IDEA(0);
    E_IDEA(1);
    E_IDEA(2);
    E_IDEA(3);
    E_IDEA(4);
    E_IDEA(5);
    E_IDEA(6);
    E_IDEA(7);

    x1 &= 0xffff;
    idea_mul(x1, x1, *p, ul);
    p++;

    t0 = x3 + *(p++);
    t1 = x2 + *(p++);

    x4 &= 0xffff;
    idea_mul(x4, x4, *p, ul);

    d[0] = (t0 & 0xffff) | ((x1 & 0xffff) << 16);
    d[1] = (x4 & 0xffff) | ((t1 & 0xffff) << 16);
}