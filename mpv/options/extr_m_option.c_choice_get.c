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
struct TYPE_2__ {int flag; int int64; int /*<<< orphan*/  string; } ;
struct mpv_node {TYPE_1__ u; int /*<<< orphan*/  format; } ;
struct m_opt_choice_alternatives {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_FORMAT_FLAG ; 
 int /*<<< orphan*/  MPV_FORMAT_INT64 ; 
 int /*<<< orphan*/  MPV_FORMAT_STRING ; 
 struct m_opt_choice_alternatives* get_choice (int /*<<< orphan*/  const*,void*,int*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int strtol (int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  talloc_strdup (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int choice_get(const m_option_t *opt, void *ta_parent,
                      struct mpv_node *dst, void *src)
{
    int ival = 0;
    struct m_opt_choice_alternatives *alt = get_choice(opt, src, &ival);
    // If a choice string looks like a number, return it as number
    if (alt) {
        char *end = NULL;
        ival = strtol(alt->name, &end, 10);
        if (end && !end[0])
            alt = NULL;
    }
    if (alt) {
        int b = -1;
        if (strcmp(alt->name, "yes") == 0) {
            b = 1;
        } else if (strcmp(alt->name, "no") == 0) {
            b = 0;
        }
        if (b >= 0) {
            dst->format = MPV_FORMAT_FLAG;
            dst->u.flag = b;
        } else {
            dst->format = MPV_FORMAT_STRING;
            dst->u.string = talloc_strdup(ta_parent, alt->name);
        }
    } else {
        dst->format = MPV_FORMAT_INT64;
        dst->u.int64 = ival;
    }
    return 1;
}