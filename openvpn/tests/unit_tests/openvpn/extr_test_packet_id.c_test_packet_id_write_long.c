#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ buf_id; scalar_t__ buf_time; } ;
struct TYPE_4__ {int id; int time; } ;
struct test_packet_id_write_data {TYPE_1__ test_buf_data; TYPE_2__ pis; int /*<<< orphan*/  test_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_true (int) ; 
 scalar_t__ htonl (int) ; 
 int now ; 
 int packet_id_write (TYPE_2__*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
test_packet_id_write_long(void **state)
{
    struct test_packet_id_write_data *data = *state;

    now = 5010;
    assert_true(packet_id_write(&data->pis, &data->test_buf, true, false));
    assert(data->pis.id == 1);
    assert(data->pis.time == now);
    assert_true(data->test_buf_data.buf_id == htonl(1));
    assert_true(data->test_buf_data.buf_time == htonl(now));
}