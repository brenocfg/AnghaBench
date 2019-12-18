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
typedef  int /*<<< orphan*/  mpv_node ;

/* Variables and functions */
 int /*<<< orphan*/  mpv_free_node_contents (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destruct_af_mpv_node(void *p)
{
    mpv_free_node_contents((mpv_node*)p);  // does nothing for MPV_FORMAT_NONE
}