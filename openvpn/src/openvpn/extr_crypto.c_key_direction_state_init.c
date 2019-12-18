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
struct key_direction_state {int out_key; int in_key; int need_keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR (struct key_direction_state) ; 
#define  KEY_DIRECTION_BIDIRECTIONAL 130 
#define  KEY_DIRECTION_INVERSE 129 
#define  KEY_DIRECTION_NORMAL 128 

void
key_direction_state_init(struct key_direction_state *kds, int key_direction)
{
    CLEAR(*kds);
    switch (key_direction)
    {
        case KEY_DIRECTION_NORMAL:
            kds->out_key = 0;
            kds->in_key = 1;
            kds->need_keys = 2;
            break;

        case KEY_DIRECTION_INVERSE:
            kds->out_key = 1;
            kds->in_key = 0;
            kds->need_keys = 2;
            break;

        case KEY_DIRECTION_BIDIRECTIONAL:
            kds->out_key = 0;
            kds->in_key = 0;
            kds->need_keys = 1;
            break;

        default:
            ASSERT(0);
    }
}