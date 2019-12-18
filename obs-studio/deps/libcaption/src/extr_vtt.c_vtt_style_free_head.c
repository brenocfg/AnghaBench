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
struct TYPE_3__ {int /*<<< orphan*/ * style_tail; int /*<<< orphan*/ * style_head; } ;
typedef  TYPE_1__ vtt_t ;

/* Variables and functions */
 int /*<<< orphan*/ * vtt_block_free_head (int /*<<< orphan*/ *) ; 

void vtt_style_free_head(vtt_t* vtt)
{
    vtt->style_head = vtt_block_free_head(vtt->style_head);
    if (vtt->style_head == NULL) {
        vtt->style_tail = NULL;
    }
}