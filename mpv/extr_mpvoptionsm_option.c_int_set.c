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
struct mpv_node {int dummy; } ;
typedef  int /*<<< orphan*/  m_option_t ;
typedef  int int64_t ;

/* Variables and functions */
 int INT_MAX ; 
 int INT_MIN ; 
 int M_OPT_OUT_OF_RANGE ; 
 int int64_set (int /*<<< orphan*/  const*,int*,struct mpv_node*) ; 

__attribute__((used)) static int int_set(const m_option_t *opt, void *dst, struct mpv_node *src)
{
    int64_t val;
    int r = int64_set(opt, &val, src);
    if (r >= 0) {
        if (val < INT_MIN || val > INT_MAX)
            return M_OPT_OUT_OF_RANGE;
        *(int *)dst = val;
    }
    return r;
}