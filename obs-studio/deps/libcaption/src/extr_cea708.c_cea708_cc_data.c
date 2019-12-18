#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* cc_data; } ;
typedef  TYPE_2__ user_data_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  cea708_cc_type_t ;
struct TYPE_4__ {int cc_valid; int /*<<< orphan*/  cc_data; int /*<<< orphan*/  cc_type; } ;

/* Variables and functions */

uint16_t cea708_cc_data(user_data_t* data, int index, int* valid, cea708_cc_type_t* type)
{
    (*valid) = data->cc_data[index].cc_valid;
    (*type) = data->cc_data[index].cc_type;
    return data->cc_data[index].cc_data;
}