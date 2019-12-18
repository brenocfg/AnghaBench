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
typedef  int uint16_t ;
struct TYPE_3__ {void* buffer; } ;
typedef  TYPE_1__ triple_buffer_object_t ;

/* Variables and functions */
 int GET_WRITE_INDEX () ; 

void* triple_buffer_begin_write_internal(uint16_t object_size, triple_buffer_object_t* object) {
    uint8_t write_index = GET_WRITE_INDEX();
    return object->buffer + object_size * write_index;
}