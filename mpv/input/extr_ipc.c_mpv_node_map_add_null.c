#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ mpv_node ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_FORMAT_NONE ; 
 int /*<<< orphan*/  mpv_node_map_add (void*,TYPE_1__*,char const*,TYPE_1__*) ; 

__attribute__((used)) static void mpv_node_map_add_null(void *ta_parent, mpv_node *src, const char *key)
{
    mpv_node val_node = {.format = MPV_FORMAT_NONE};
    mpv_node_map_add(ta_parent, src, key, &val_node);
}