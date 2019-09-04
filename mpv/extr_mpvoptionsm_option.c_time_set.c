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
struct TYPE_2__ {int /*<<< orphan*/  string; } ;
struct mpv_node {scalar_t__ format; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
 scalar_t__ HAS_NOPTS (int /*<<< orphan*/  const*) ; 
 scalar_t__ MPV_FORMAT_STRING ; 
 double MP_NOPTS_VALUE ; 
 int double_set (int /*<<< orphan*/  const*,void*,struct mpv_node*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int time_set(const m_option_t *opt, void *dst, struct mpv_node *src)
{
    if (HAS_NOPTS(opt) && src->format == MPV_FORMAT_STRING) {
        if (strcmp(src->u.string, "no") == 0) {
            *(double *)dst = MP_NOPTS_VALUE;
            return 1;
        }
    }
    return double_set(opt, dst, src);
}