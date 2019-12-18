#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int capacity; void* data; } ;
struct test_packet_id_write_data {TYPE_1__ test_buf; int /*<<< orphan*/  test_buf_data; } ;

/* Variables and functions */
 struct test_packet_id_write_data* calloc (int,int) ; 

__attribute__((used)) static int
test_packet_id_write_setup(void **state) {
    struct test_packet_id_write_data *data =
            calloc(1, sizeof(struct test_packet_id_write_data));

    if (!data)
    {
        return -1;
    }

    data->test_buf.data = (void *) &data->test_buf_data;
    data->test_buf.capacity = sizeof(data->test_buf_data);

    *state = data;
    return 0;
}