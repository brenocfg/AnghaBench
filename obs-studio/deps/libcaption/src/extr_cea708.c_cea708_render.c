#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int em_data; int cc_count; TYPE_1__* cc_data; scalar_t__ additional_data_flag; scalar_t__ process_cc_data_flag; scalar_t__ process_em_data_flag; } ;
struct TYPE_7__ {int country; int provider; int user_identifier; int user_data_type_code; int directv_user_data_length; TYPE_2__ user_data; } ;
typedef  TYPE_3__ cea708_t ;
struct TYPE_5__ {int marker_bits; int cc_valid; int cc_type; int cc_data; } ;

/* Variables and functions */
 int t35_provider_atsc ; 
 int t35_provider_direct_tv ; 

int cea708_render(cea708_t* cea708, uint8_t* data, size_t size)
{
    int i;
    size_t total = 0;
    data[0] = cea708->country;
    data[1] = cea708->provider >> 8;
    data[2] = cea708->provider >> 0;
    total += 3;
    data += 3;
    size -= 3;

    if (t35_provider_atsc == cea708->provider) {

        data[0] = cea708->user_identifier >> 24;
        data[1] = cea708->user_identifier >> 16;
        data[2] = cea708->user_identifier >> 8;
        data[3] = cea708->user_identifier >> 0;
        total += 4;
        data += 4;
        size -= 4;
    }

    if (t35_provider_atsc == cea708->provider || t35_provider_direct_tv == cea708->provider) {
        data[0] = cea708->user_data_type_code;
        total += 1;
        data += 1;
        size -= 1;
    }

    if (t35_provider_direct_tv == cea708->provider) {
        data[0] = cea708->directv_user_data_length;
        total += 1;
        data += 1;
        size -= 1;
    }

    data[1] = cea708->user_data.em_data;
    data[0] = (cea708->user_data.process_em_data_flag ? 0x80 : 0x00)
        | (cea708->user_data.process_cc_data_flag ? 0x40 : 0x00)
        | (cea708->user_data.additional_data_flag ? 0x20 : 0x00)
        | (cea708->user_data.cc_count & 0x1F);

    total += 2;
    data += 2;
    size -= 2;

    for (i = 0; i < (int)cea708->user_data.cc_count; ++i) {
        data[0] = (cea708->user_data.cc_data[i].marker_bits << 3) | (cea708->user_data.cc_data[i].cc_valid << 2) | cea708->user_data.cc_data[i].cc_type;
        data[1] = cea708->user_data.cc_data[i].cc_data >> 8;
        data[2] = cea708->user_data.cc_data[i].cc_data >> 0;
        total += 3;
        data += 3;
        size -= 3;
    }

    data[0] = 0xFF; //marker bits
    return (int)(total + 1);
}