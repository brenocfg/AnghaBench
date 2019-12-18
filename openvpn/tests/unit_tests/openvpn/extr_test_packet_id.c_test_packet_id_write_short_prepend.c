#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ buf_id; scalar_t__ buf_time; } ;
struct TYPE_5__ {int id; } ;
struct TYPE_6__ {int offset; } ;
struct test_packet_id_write_data {TYPE_1__ test_buf_data; TYPE_2__ pis; TYPE_3__ test_buf; } ;
typedef  int /*<<< orphan*/  packet_id_type ;

/* Variables and functions */
 int /*<<< orphan*/  assert_true (int) ; 
 scalar_t__ htonl (int) ; 
 int now ; 
 int packet_id_write (TYPE_2__*,TYPE_3__*,int,int) ; 

__attribute__((used)) static void
test_packet_id_write_short_prepend(void **state)
{
    struct test_packet_id_write_data *data = *state;

    data->test_buf.offset = sizeof(packet_id_type);
    now = 5010;
    assert_true(packet_id_write(&data->pis, &data->test_buf, false, true));
    assert_true(data->pis.id == 1);
    assert_true(data->test_buf_data.buf_id == htonl(1));
    assert_true(data->test_buf_data.buf_time == 0);
}