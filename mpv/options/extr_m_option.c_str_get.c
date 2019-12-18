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
struct mpv_node {TYPE_1__ u; int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_FORMAT_STRING ; 
 char* VAL (void*) ; 
 int /*<<< orphan*/  talloc_strdup (void*,char*) ; 

__attribute__((used)) static int str_get(const m_option_t *opt, void *ta_parent,
                   struct mpv_node *dst, void *src)
{
    dst->format = MPV_FORMAT_STRING;
    dst->u.string = talloc_strdup(ta_parent, VAL(src) ? VAL(src) : "");
    return 1;
}