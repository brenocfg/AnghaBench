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
struct dlm_comm {int dummy; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 struct dlm_comm* config_item_to_comm (struct config_item*) ; 
 int /*<<< orphan*/  kfree (struct dlm_comm*) ; 

__attribute__((used)) static void release_comm(struct config_item *i)
{
	struct dlm_comm *cm = config_item_to_comm(i);
	kfree(cm);
}