#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mp_pin {struct mp_filter* manual_connection; } ;
struct mp_filter {int dummy; } ;

/* Variables and functions */

struct mp_filter *mp_pin_get_manual_connection(struct mp_pin *p)
{
    return p->manual_connection;
}