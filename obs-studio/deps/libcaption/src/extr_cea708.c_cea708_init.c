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
struct TYPE_5__ {int process_cc_data_flag; int em_data; scalar_t__ cc_count; scalar_t__ additional_data_flag; scalar_t__ process_em_data_flag; } ;
struct TYPE_6__ {int user_data_type_code; double timestamp; TYPE_1__ user_data; scalar_t__ directv_user_data_length; int /*<<< orphan*/  user_identifier; int /*<<< orphan*/  provider; int /*<<< orphan*/  country; } ;
typedef  TYPE_2__ cea708_t ;

/* Variables and functions */
 int /*<<< orphan*/  GA94 ; 
 int /*<<< orphan*/  country_united_states ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t35_provider_atsc ; 

int cea708_init(cea708_t* cea708, double timestamp)
{
    memset(cea708, 0, sizeof(cea708_t));
    cea708->country = country_united_states;
    cea708->provider = t35_provider_atsc;
    cea708->user_identifier = GA94;
    cea708->user_data_type_code = 3;
    cea708->directv_user_data_length = 0;
    cea708->user_data.process_em_data_flag = 0;
    cea708->user_data.process_cc_data_flag = 1;
    cea708->user_data.additional_data_flag = 0;
    cea708->user_data.em_data = 0xFF;
    cea708->user_data.cc_count = 0;
    cea708->timestamp = timestamp;
    return 1;
}