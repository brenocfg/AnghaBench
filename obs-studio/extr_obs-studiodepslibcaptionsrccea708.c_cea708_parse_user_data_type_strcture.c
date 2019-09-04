#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int process_em_data_flag; int process_cc_data_flag; int additional_data_flag; int cc_count; int em_data; TYPE_1__* cc_data; } ;
typedef  TYPE_2__ user_data_t ;
typedef  int uint8_t ;
struct TYPE_5__ {int marker_bits; int cc_valid; int cc_type; int cc_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void cea708_parse_user_data_type_strcture(const uint8_t* data, size_t size, user_data_t* user_data)
{
    memset(user_data, 0, sizeof(user_data_t));
    user_data->process_em_data_flag = !!(data[0] & 0x80);
    user_data->process_cc_data_flag = !!(data[0] & 0x40);
    user_data->additional_data_flag = !!(data[0] & 0x20);
    user_data->cc_count = (data[0] & 0x1F);
    user_data->em_data = data[1];
    data += 2, size -= 2;

    for (int i = 0; 3 < size && i < (int)user_data->cc_count; ++i, data += 3, size -= 3) {
        user_data->cc_data[i].marker_bits = data[0] >> 3;
        user_data->cc_data[i].cc_valid = data[0] >> 2;
        user_data->cc_data[i].cc_type = data[0] >> 0;
        user_data->cc_data[i].cc_data = data[1] << 8 | data[2];
    }
}