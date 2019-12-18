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
struct TYPE_4__ {int num; char** items; } ;
struct TYPE_5__ {TYPE_1__ subscriptions; } ;
typedef  TYPE_2__ nn_options_t ;

/* Variables and functions */
 int /*<<< orphan*/  NN_SUB ; 
 int /*<<< orphan*/  NN_SUB_SUBSCRIBE ; 
 int /*<<< orphan*/  nn_assert_errno (int,char*) ; 
 int nn_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void nn_sub_init (nn_options_t *options, int sock)
{
    int i;
    int rc;

    if (options->subscriptions.num) {
        for (i = 0; i < options->subscriptions.num; ++i) {
            rc = nn_setsockopt (sock, NN_SUB, NN_SUB_SUBSCRIBE,
                options->subscriptions.items[i],
                strlen (options->subscriptions.items[i]));
            nn_assert_errno (rc == 0, "Can't subscribe");
        }
    } else {
        rc = nn_setsockopt (sock, NN_SUB, NN_SUB_SUBSCRIBE, "", 0);
        nn_assert_errno (rc == 0, "Can't subscribe");
    }
}