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
struct TYPE_3__ {scalar_t__ state; } ;
typedef  TYPE_1__ triple_buffer_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  SET_DATA_AVAILABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_READ_INDEX (int) ; 
 int /*<<< orphan*/  SET_SHARED_INDEX (int) ; 
 int /*<<< orphan*/  SET_WRITE_INDEX (int /*<<< orphan*/ ) ; 

void triple_buffer_init(triple_buffer_object_t* object) {
    object->state = 0;
    SET_WRITE_INDEX(0);
    SET_READ_INDEX(1);
    SET_SHARED_INDEX(2);
    SET_DATA_AVAILABLE(0);
}