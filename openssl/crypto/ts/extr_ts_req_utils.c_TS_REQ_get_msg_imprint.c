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
struct TYPE_3__ {int /*<<< orphan*/ * msg_imprint; } ;
typedef  TYPE_1__ TS_REQ ;
typedef  int /*<<< orphan*/  TS_MSG_IMPRINT ;

/* Variables and functions */

TS_MSG_IMPRINT *TS_REQ_get_msg_imprint(TS_REQ *a)
{
    return a->msg_imprint;
}