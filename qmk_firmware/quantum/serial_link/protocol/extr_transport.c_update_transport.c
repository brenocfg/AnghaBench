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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  triple_buffer_object_t ;
struct TYPE_3__ {scalar_t__ object_type; int* buffer; size_t object_size; } ;
typedef  TYPE_1__ remote_object_t ;

/* Variables and functions */
 scalar_t__ LOCAL_OBJECT_EXTRA ; 
 int /*<<< orphan*/  LOCAL_OBJECT_SIZE (size_t) ; 
 scalar_t__ MASTER_TO_ALL_SLAVES ; 
 unsigned int NUM_SLAVES ; 
 scalar_t__ SLAVE_TO_MASTER ; 
 unsigned int num_remote_objects ; 
 TYPE_1__** remote_objects ; 
 int /*<<< orphan*/  router_send_frame (int,int*,size_t) ; 
 scalar_t__ triple_buffer_read_internal (scalar_t__,int /*<<< orphan*/ *) ; 

void update_transport(void) {
    unsigned int i;
    for (i = 0; i < num_remote_objects; i++) {
        remote_object_t* obj = remote_objects[i];
        if (obj->object_type == MASTER_TO_ALL_SLAVES || obj->object_type == SLAVE_TO_MASTER) {
            triple_buffer_object_t* tb  = (triple_buffer_object_t*)obj->buffer;
            uint8_t*                ptr = (uint8_t*)triple_buffer_read_internal(obj->object_size + LOCAL_OBJECT_EXTRA, tb);
            if (ptr) {
                ptr[obj->object_size] = i;
                uint8_t dest          = obj->object_type == MASTER_TO_ALL_SLAVES ? 0xFF : 0;
                router_send_frame(dest, ptr, obj->object_size + 1);
            }
        } else {
            uint8_t*     start = obj->buffer;
            unsigned int j;
            for (j = 0; j < NUM_SLAVES; j++) {
                triple_buffer_object_t* tb  = (triple_buffer_object_t*)start;
                uint8_t*                ptr = (uint8_t*)triple_buffer_read_internal(obj->object_size + LOCAL_OBJECT_EXTRA, tb);
                if (ptr) {
                    ptr[obj->object_size] = i;
                    uint8_t dest          = j + 1;
                    router_send_frame(dest, ptr, obj->object_size + 1);
                }
                start += LOCAL_OBJECT_SIZE(obj->object_size);
            }
        }
    }
}