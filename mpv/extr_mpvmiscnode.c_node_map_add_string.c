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
struct TYPE_2__ {int /*<<< orphan*/  list; int /*<<< orphan*/  string; } ;
struct mpv_node {TYPE_1__ u; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_FORMAT_NONE ; 
 int /*<<< orphan*/  MPV_FORMAT_STRING ; 
 int /*<<< orphan*/  assert (char const*) ; 
 struct mpv_node* node_map_add (struct mpv_node*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_strdup (int /*<<< orphan*/ ,char const*) ; 

void node_map_add_string(struct mpv_node *dst, const char *key, const char *val)
{
    assert(val);

    struct mpv_node *entry = node_map_add(dst, key, MPV_FORMAT_NONE);
    entry->format = MPV_FORMAT_STRING;
    entry->u.string = talloc_strdup(dst->u.list, val);
}