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
typedef  size_t uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  triple_buffer_object_t ;
struct TYPE_3__ {int object_size; scalar_t__ object_type; size_t* buffer; } ;
typedef  TYPE_1__ remote_object_t ;

/* Variables and functions */
 int LOCAL_OBJECT_SIZE (int) ; 
 scalar_t__ MASTER_TO_ALL_SLAVES ; 
 int NUM_SLAVES ; 
 size_t REMOTE_OBJECT_SIZE (int) ; 
 scalar_t__ SLAVE_TO_MASTER ; 
 int /*<<< orphan*/  memcpy (void*,size_t*,int) ; 
 size_t num_remote_objects ; 
 TYPE_1__** remote_objects ; 
 void* triple_buffer_begin_write_internal (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  triple_buffer_end_write_internal (int /*<<< orphan*/ *) ; 

void transport_recv_frame(uint8_t from, uint8_t* data, uint16_t size) {
    uint8_t id = data[size - 1];
    if (id < num_remote_objects) {
        remote_object_t* obj = remote_objects[id];
        if (obj->object_size == size - 1) {
            uint8_t* start;
            if (obj->object_type == MASTER_TO_ALL_SLAVES) {
                start = obj->buffer + LOCAL_OBJECT_SIZE(obj->object_size);
            } else if (obj->object_type == SLAVE_TO_MASTER) {
                start = obj->buffer + LOCAL_OBJECT_SIZE(obj->object_size);
                start += (from - 1) * REMOTE_OBJECT_SIZE(obj->object_size);
            } else {
                start = obj->buffer + NUM_SLAVES * LOCAL_OBJECT_SIZE(obj->object_size);
            }
            triple_buffer_object_t* tb  = (triple_buffer_object_t*)start;
            void*                   ptr = triple_buffer_begin_write_internal(obj->object_size, tb);
            memcpy(ptr, data, size - 1);
            triple_buffer_end_write_internal(tb);
        }
    }
}