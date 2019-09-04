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
struct mpvs_fmt {int /*<<< orphan*/  vs; scalar_t__ bits; } ;
typedef  int /*<<< orphan*/  VSPresetFormat ;

/* Variables and functions */
 scalar_t__ compare_fmt (int,struct mpvs_fmt const*) ; 
 struct mpvs_fmt* mpvs_fmt_table ; 
 int /*<<< orphan*/  pfNone ; 

__attribute__((used)) static VSPresetFormat mp_to_vs(int imgfmt)
{
    for (int n = 0; mpvs_fmt_table[n].bits; n++) {
        const struct mpvs_fmt *vsentry = &mpvs_fmt_table[n];
        if (compare_fmt(imgfmt, vsentry))
            return vsentry->vs;
    }
    return pfNone;
}