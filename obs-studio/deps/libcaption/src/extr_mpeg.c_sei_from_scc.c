#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_2__ sei_t ;
struct TYPE_13__ {unsigned int cc_size; int /*<<< orphan*/ * cc_data; } ;
typedef  TYPE_3__ scc_t ;
typedef  int /*<<< orphan*/  libcaption_stauts_t ;
struct TYPE_11__ {int cc_count; } ;
struct TYPE_14__ {TYPE_1__ user_data; } ;
typedef  TYPE_4__ cea708_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIBCAPTION_OK ; 
 int /*<<< orphan*/  cc_type_ntsc_cc_field_1 ; 
 int /*<<< orphan*/  cea708_add_cc_data (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cea708_init (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sei_append_708 (TYPE_2__*,TYPE_4__*) ; 

libcaption_stauts_t sei_from_scc(sei_t* sei, const scc_t* scc)
{
    unsigned int i;
    cea708_t cea708;
    cea708_init(&cea708, sei->timestamp); // set up a new popon frame

    for (i = 0; i < scc->cc_size; ++i) {
        if (31 == cea708.user_data.cc_count) {
            sei_append_708(sei, &cea708);
        }

        cea708_add_cc_data(&cea708, 1, cc_type_ntsc_cc_field_1, scc->cc_data[i]);
    }

    if (0 != cea708.user_data.cc_count) {
        sei_append_708(sei, &cea708);
    }

    return LIBCAPTION_OK;
}