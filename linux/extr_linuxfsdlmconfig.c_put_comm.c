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
struct dlm_comm {int /*<<< orphan*/  item; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_comm(struct dlm_comm *cm)
{
	config_item_put(&cm->item);
}