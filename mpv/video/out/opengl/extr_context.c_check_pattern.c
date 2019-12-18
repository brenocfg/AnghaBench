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
struct priv {size_t last_pattern; int /*<<< orphan*/  mismatches; int /*<<< orphan*/  matches; TYPE_1__* opts; } ;
struct TYPE_2__ {int* vsync_pattern; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WARN (struct priv*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_pattern(struct priv *p, int item)
{
    int expected = p->opts->vsync_pattern[p->last_pattern];
    if (item == expected) {
        p->last_pattern++;
        if (p->last_pattern >= 2)
            p->last_pattern = 0;
        p->matches++;
    } else {
        p->mismatches++;
        MP_WARN(p, "wrong pattern, expected %d got %d (hit: %d, mis: %d)\n",
                expected, item, p->matches, p->mismatches);
    }
}