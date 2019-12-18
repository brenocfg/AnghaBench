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
struct ima_template_entry {int dummy; } ;

/* Variables and functions */
 int ima_add_digest_entry (struct ima_template_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ima_extend_list_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ima_restore_measurement_entry(struct ima_template_entry *entry)
{
	int result = 0;

	mutex_lock(&ima_extend_list_mutex);
	result = ima_add_digest_entry(entry, 0);
	mutex_unlock(&ima_extend_list_mutex);
	return result;
}