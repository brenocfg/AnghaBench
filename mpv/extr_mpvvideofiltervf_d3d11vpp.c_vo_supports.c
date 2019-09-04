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
struct priv {int* vo_formats; } ;

/* Variables and functions */

__attribute__((used)) static bool vo_supports(struct priv *p, int subfmt)
{
    for (int n = 0; p->vo_formats && p->vo_formats[n]; n++) {
        if (p->vo_formats[n] == subfmt)
            return true;
    }
    return false;
}