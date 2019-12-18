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
struct TYPE_2__ {int int64; } ;
struct mpv_node {TYPE_1__ u; int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_FORMAT_INT64 ; 

__attribute__((used)) static int int_get(const m_option_t *opt, void *ta_parent,
                   struct mpv_node *dst, void *src)
{
    dst->format = MPV_FORMAT_INT64;
    dst->u.int64 = *(int *)src;
    return 1;
}