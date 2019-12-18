#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* string; } ;
struct TYPE_7__ {TYPE_1__ u; int /*<<< orphan*/  format; } ;
typedef  TYPE_2__ mpv_node ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_FORMAT_STRING ; 
 int /*<<< orphan*/  mpv_node_array_add (void*,TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static void mpv_node_array_add_string(void *ta_parent, mpv_node *src, const char *val)
{
    mpv_node val_node = {.format = MPV_FORMAT_STRING, .u.string = (char *)val};
    mpv_node_array_add(ta_parent, src, &val_node);
}