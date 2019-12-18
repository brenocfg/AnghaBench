#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* d; int /*<<< orphan*/  write_sequence; } ;
struct TYPE_4__ {int w_epoch; int /*<<< orphan*/  curr_write_sequence; int /*<<< orphan*/  last_write_sequence; } ;
typedef  TYPE_2__ RECORD_LAYER ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void DTLS_RECORD_LAYER_set_saved_w_epoch(RECORD_LAYER *rl, unsigned short e)
{
    if (e == rl->d->w_epoch - 1) {
        memcpy(rl->d->curr_write_sequence,
               rl->write_sequence, sizeof(rl->write_sequence));
        memcpy(rl->write_sequence,
               rl->d->last_write_sequence, sizeof(rl->write_sequence));
    } else if (e == rl->d->w_epoch + 1) {
        memcpy(rl->d->last_write_sequence,
               rl->write_sequence, sizeof(unsigned char[8]));
        memcpy(rl->write_sequence,
               rl->d->curr_write_sequence, sizeof(rl->write_sequence));
    }
    rl->d->w_epoch = e;
}