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
typedef  TYPE_1__ TS_TST_INFO ;
typedef  int /*<<< orphan*/  TS_MSG_IMPRINT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  TS_F_TS_TST_INFO_SET_MSG_IMPRINT ; 
 int /*<<< orphan*/ * TS_MSG_IMPRINT_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_MSG_IMPRINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int TS_TST_INFO_set_msg_imprint(TS_TST_INFO *a, TS_MSG_IMPRINT *msg_imprint)
{
    TS_MSG_IMPRINT *new_msg_imprint;

    if (a->msg_imprint == msg_imprint)
        return 1;
    new_msg_imprint = TS_MSG_IMPRINT_dup(msg_imprint);
    if (new_msg_imprint == NULL) {
        TSerr(TS_F_TS_TST_INFO_SET_MSG_IMPRINT, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    TS_MSG_IMPRINT_free(a->msg_imprint);
    a->msg_imprint = new_msg_imprint;
    return 1;
}