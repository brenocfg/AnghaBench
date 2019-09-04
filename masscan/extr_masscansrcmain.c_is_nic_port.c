#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct Masscan {unsigned int nic_count; TYPE_1__* nic; } ;
struct TYPE_2__ {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 scalar_t__ is_my_port (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static unsigned
is_nic_port(const struct Masscan *masscan, unsigned ip)
{
    unsigned i;
    for (i=0; i<masscan->nic_count; i++)
        if (is_my_port(&masscan->nic[i].src, ip))
            return 1;
    return 0;
}