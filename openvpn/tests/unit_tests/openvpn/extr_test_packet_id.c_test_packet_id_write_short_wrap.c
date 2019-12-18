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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct test_packet_id_write_data {int /*<<< orphan*/  test_buf; TYPE_1__ pis; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_id_write (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
test_packet_id_write_short_wrap(void **state)
{
    struct test_packet_id_write_data *data = *state;

    data->pis.id = ~0;
    assert_false(packet_id_write(&data->pis, &data->test_buf, false, false));
}