#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ cmd; int substate; } ;
typedef  TYPE_1__ conn ;

/* Variables and functions */
 scalar_t__ PROTOCOL_BINARY_CMD_APPEND ; 
 scalar_t__ PROTOCOL_BINARY_CMD_PREPEND ; 
 int /*<<< orphan*/  assert (int) ; 
#define  bin_read_flush_exptime 137 
#define  bin_read_set_value 136 
#define  bin_reading_del_header 135 
#define  bin_reading_get_key 134 
#define  bin_reading_incr_header 133 
#define  bin_reading_sasl_auth 132 
#define  bin_reading_sasl_auth_data 131 
#define  bin_reading_set_header 130 
#define  bin_reading_stat 129 
#define  bin_reading_touch_key 128 
 int /*<<< orphan*/  complete_incr_bin (TYPE_1__*) ; 
 int /*<<< orphan*/  complete_update_bin (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  process_bin_append_prepend (TYPE_1__*) ; 
 int /*<<< orphan*/  process_bin_complete_sasl_auth (TYPE_1__*) ; 
 int /*<<< orphan*/  process_bin_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  process_bin_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  process_bin_get_or_touch (TYPE_1__*) ; 
 int /*<<< orphan*/  process_bin_sasl_auth (TYPE_1__*) ; 
 int /*<<< orphan*/  process_bin_stat (TYPE_1__*) ; 
 int /*<<< orphan*/  process_bin_update (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void complete_nread_binary(conn *c) {
    assert(c != NULL);
    assert(c->cmd >= 0);

    switch(c->substate) {
    case bin_reading_set_header:
        if (c->cmd == PROTOCOL_BINARY_CMD_APPEND ||
                c->cmd == PROTOCOL_BINARY_CMD_PREPEND) {
            process_bin_append_prepend(c);
        } else {
            process_bin_update(c);
        }
        break;
    case bin_read_set_value:
        complete_update_bin(c);
        break;
    case bin_reading_get_key:
    case bin_reading_touch_key:
        process_bin_get_or_touch(c);
        break;
    case bin_reading_stat:
        process_bin_stat(c);
        break;
    case bin_reading_del_header:
        process_bin_delete(c);
        break;
    case bin_reading_incr_header:
        complete_incr_bin(c);
        break;
    case bin_read_flush_exptime:
        process_bin_flush(c);
        break;
    case bin_reading_sasl_auth:
        process_bin_sasl_auth(c);
        break;
    case bin_reading_sasl_auth_data:
        process_bin_complete_sasl_auth(c);
        break;
    default:
        fprintf(stderr, "Not handling substate %d\n", c->substate);
        assert(0);
    }
}