#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ col; scalar_t__ row; } ;
struct TYPE_8__ {TYPE_1__ key; } ;
struct TYPE_9__ {TYPE_2__ event; } ;
struct TYPE_10__ {TYPE_3__ record; } ;
typedef  TYPE_4__ pending_key_t ;

/* Variables and functions */

bool keys_match(pending_key_t *a, pending_key_t *b) {
    return a->record.event.key.col == b->record.event.key.col
        && a->record.event.key.row == b->record.event.key.row;
}