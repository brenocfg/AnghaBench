#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int* state; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_1__ arc4_info ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,scalar_t__ const*,unsigned int) ; 

void SECUR32_arc4Init(arc4_info *a4i, const BYTE *key, unsigned int keyLen)
{
    unsigned int keyIndex = 0, stateIndex = 0;
    unsigned int i, a;

    TRACE("(%p, %p, %d)\n", a4i, key, keyLen);

        a4i->x = a4i->y = 0;

    for (i=0; i<256; i++)
        a4i->state[i] = i;

    for (i=0; i<256; i++)
    {
        a = a4i->state[i];
        stateIndex += key[keyIndex] + a;
        stateIndex &= 0xff;
        a4i->state[i] = a4i->state[stateIndex];
        a4i->state[stateIndex] = a;
        if (++keyIndex >= keyLen)
            keyIndex = 0;
    }

}