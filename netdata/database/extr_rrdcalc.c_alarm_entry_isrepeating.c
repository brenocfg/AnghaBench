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
struct TYPE_3__ {int /*<<< orphan*/  alarm_id; } ;
typedef  int /*<<< orphan*/  RRDHOST ;
typedef  TYPE_1__ ALARM_ENTRY ;

/* Variables and functions */
 int alarm_isrepeating (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int alarm_entry_isrepeating(RRDHOST *host, ALARM_ENTRY *ae) {
    return alarm_isrepeating(host, ae->alarm_id);
}