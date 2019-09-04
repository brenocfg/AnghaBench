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
struct esp_cmd_entry {int /*<<< orphan*/  list; } ;
struct esp {int /*<<< orphan*/  esp_cmd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esp_put_ent(struct esp *esp, struct esp_cmd_entry *ent)
{
	list_add(&ent->list, &esp->esp_cmd_pool);
}