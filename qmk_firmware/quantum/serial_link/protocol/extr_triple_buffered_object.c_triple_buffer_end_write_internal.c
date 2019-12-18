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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  triple_buffer_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_SHARED_INDEX () ; 
 int /*<<< orphan*/  GET_WRITE_INDEX () ; 
 int /*<<< orphan*/  SET_DATA_AVAILABLE (int) ; 
 int /*<<< orphan*/  SET_SHARED_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_WRITE_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_link_lock () ; 
 int /*<<< orphan*/  serial_link_unlock () ; 

void triple_buffer_end_write_internal(triple_buffer_object_t* object) {
    serial_link_lock();
    uint8_t shared_index = GET_SHARED_INDEX();
    uint8_t write_index  = GET_WRITE_INDEX();
    SET_SHARED_INDEX(write_index);
    SET_WRITE_INDEX(shared_index);
    SET_DATA_AVAILABLE(true);
    serial_link_unlock();
}