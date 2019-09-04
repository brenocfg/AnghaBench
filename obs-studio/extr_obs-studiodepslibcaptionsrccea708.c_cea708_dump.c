#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {int process_em_data_flag; int process_cc_data_flag; int additional_data_flag; int cc_count; int em_data; TYPE_1__* cc_data; } ;
struct TYPE_6__ {int country; int provider; int user_identifier; int user_data_type_code; int directv_user_data_length; TYPE_4__ user_data; } ;
typedef  TYPE_2__ cea708_t ;
typedef  scalar_t__ cea708_cc_type_t ;
struct TYPE_5__ {int cc_type; int cc_data; scalar_t__ cc_valid; } ;

/* Variables and functions */
 scalar_t__ cc_type_ntsc_cc_field_1 ; 
 int /*<<< orphan*/  cea708_cc_data (TYPE_4__*,int,int*,scalar_t__*) ; 
 int /*<<< orphan*/  eia608_dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  stderr ; 

void cea708_dump(cea708_t* cea708)
{
    int i;

    fprintf(stderr, "itu_t_t35_country_code_t %d\n", cea708->country);
    fprintf(stderr, "itu_t_t35_provider_code_t %d\n", cea708->provider);
    fprintf(stderr, "user_identifier %c%c%c%c\n",
        (cea708->user_identifier >> 24) & 0xFF, (cea708->user_identifier >> 16) & 0xFF,
        (cea708->user_identifier >> 8) & 0xFF, cea708->user_identifier & 0xFF);
    fprintf(stderr, "user_data_type_code %d\n", cea708->user_data_type_code);
    fprintf(stderr, "directv_user_data_length %d\n", cea708->directv_user_data_length);
    fprintf(stderr, "user_data.process_em_data_flag %d\n", cea708->user_data.process_em_data_flag);
    fprintf(stderr, "user_data.process_cc_data_flag %d\n", cea708->user_data.process_cc_data_flag);
    fprintf(stderr, "user_data.additional_data_flag %d\n", cea708->user_data.additional_data_flag);
    fprintf(stderr, "user_data.cc_count %d\n", cea708->user_data.cc_count);
    fprintf(stderr, "user_data.em_data %d\n", cea708->user_data.em_data);

    for (i = 0; i < (int)cea708->user_data.cc_count; ++i) {
        int valid;
        cea708_cc_type_t type;
        uint16_t cc_data = cea708_cc_data(&cea708->user_data, i, &valid, &type);

        if (valid && cc_type_ntsc_cc_field_1 == type) {
            eia608_dump(cc_data);
        } else {
            fprintf(stderr, "user_data.cc_data[%d] cc_valid: %s, cc_type: %d, cc_data: %04x\n", i, cea708->user_data.cc_data[i].cc_valid ? "true" : "false", cea708->user_data.cc_data[i].cc_type, cea708->user_data.cc_data[i].cc_data);
        }
    }
}