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
struct grub_fshelp_find_file_closure {scalar_t__ rootnode; scalar_t__ currroot; } ;
typedef  scalar_t__ grub_fshelp_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  grub_free (scalar_t__) ; 

__attribute__((used)) static void
free_node (grub_fshelp_node_t node, struct grub_fshelp_find_file_closure *c)
{
  if (node != c->rootnode && node != c->currroot)
    grub_free (node);
}