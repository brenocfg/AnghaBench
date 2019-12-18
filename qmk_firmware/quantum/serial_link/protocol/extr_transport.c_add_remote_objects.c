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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  triple_buffer_object_t ;
struct TYPE_4__ {scalar_t__ object_type; int /*<<< orphan*/  object_size; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ remote_object_t ;

/* Variables and functions */
 int LOCAL_OBJECT_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ MASTER_TO_ALL_SLAVES ; 
 scalar_t__ MASTER_TO_SINGLE_SLAVE ; 
 unsigned int NUM_SLAVES ; 
 int /*<<< orphan*/  REMOTE_OBJECT_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_remote_objects ; 
 TYPE_1__** remote_objects ; 
 int /*<<< orphan*/  triple_buffer_init (int /*<<< orphan*/ *) ; 

void add_remote_objects(remote_object_t** _remote_objects, uint32_t _num_remote_objects) {
    unsigned int i;
    for (i = 0; i < _num_remote_objects; i++) {
        remote_object_t* obj                 = _remote_objects[i];
        remote_objects[num_remote_objects++] = obj;
        if (obj->object_type == MASTER_TO_ALL_SLAVES) {
            triple_buffer_object_t* tb = (triple_buffer_object_t*)obj->buffer;
            triple_buffer_init(tb);
            uint8_t* start = obj->buffer + LOCAL_OBJECT_SIZE(obj->object_size);
            tb             = (triple_buffer_object_t*)start;
            triple_buffer_init(tb);
        } else if (obj->object_type == MASTER_TO_SINGLE_SLAVE) {
            uint8_t*     start = obj->buffer;
            unsigned int j;
            for (j = 0; j < NUM_SLAVES; j++) {
                triple_buffer_object_t* tb = (triple_buffer_object_t*)start;
                triple_buffer_init(tb);
                start += LOCAL_OBJECT_SIZE(obj->object_size);
            }
            triple_buffer_object_t* tb = (triple_buffer_object_t*)start;
            triple_buffer_init(tb);
        } else {
            uint8_t*                start = obj->buffer;
            triple_buffer_object_t* tb    = (triple_buffer_object_t*)start;
            triple_buffer_init(tb);
            start += LOCAL_OBJECT_SIZE(obj->object_size);
            unsigned int j;
            for (j = 0; j < NUM_SLAVES; j++) {
                tb = (triple_buffer_object_t*)start;
                triple_buffer_init(tb);
                start += REMOTE_OBJECT_SIZE(obj->object_size);
            }
        }
    }
}