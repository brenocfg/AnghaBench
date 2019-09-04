#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  cea708_cc_type_t ;
struct TYPE_3__ {int member_0; int member_1; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_1__ cc_data_t ;

/* Variables and functions */

cc_data_t cea708_encode_cc_data(int cc_valid, cea708_cc_type_t type, uint16_t cc_data)
{
    cc_data_t data = { 0x1F, cc_valid, type, cc_data };
    return data;
}