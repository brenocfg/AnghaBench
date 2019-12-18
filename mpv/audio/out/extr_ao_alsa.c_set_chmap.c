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
struct mp_chmap {int dummy; } ;
struct ao {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int set_chmap(struct ao *ao, struct mp_chmap *dev_chmap, int num_channels)
{
    return 0;
}