#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_13__ {int /*<<< orphan*/  pressed; int /*<<< orphan*/  key; } ;
struct TYPE_9__ {int count; } ;
struct TYPE_10__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_12__ {TYPE_2__ tap; TYPE_3__ event; } ;
struct TYPE_8__ {int count; } ;
struct TYPE_11__ {TYPE_1__ tap; TYPE_7__ event; } ;

/* Variables and functions */
 scalar_t__ IS_TAPPING_KEY (int /*<<< orphan*/ ) ; 
 int WAITING_BUFFER_SIZE ; 
 scalar_t__ WITHIN_TAPPING_TERM (TYPE_7__) ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug_dec (int) ; 
 int /*<<< orphan*/  debug_waiting_buffer () ; 
 int /*<<< orphan*/  process_record (TYPE_5__*) ; 
 TYPE_5__ tapping_key ; 
 TYPE_4__* waiting_buffer ; 
 int waiting_buffer_head ; 
 int waiting_buffer_tail ; 

void waiting_buffer_scan_tap(void) {
    // tapping already is settled
    if (tapping_key.tap.count > 0) return;
    // invalid state: tapping_key released && tap.count == 0
    if (!tapping_key.event.pressed) return;

    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        if (IS_TAPPING_KEY(waiting_buffer[i].event.key) && !waiting_buffer[i].event.pressed && WITHIN_TAPPING_TERM(waiting_buffer[i].event)) {
            tapping_key.tap.count       = 1;
            waiting_buffer[i].tap.count = 1;
            process_record(&tapping_key);

            debug("waiting_buffer_scan_tap: found at [");
            debug_dec(i);
            debug("]\n");
            debug_waiting_buffer();
            return;
        }
    }
}