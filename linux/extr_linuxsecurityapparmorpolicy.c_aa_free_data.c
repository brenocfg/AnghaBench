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
struct aa_data {struct aa_data* key; struct aa_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kzfree (struct aa_data*) ; 

__attribute__((used)) static void aa_free_data(void *ptr, void *arg)
{
	struct aa_data *data = ptr;

	kzfree(data->data);
	kzfree(data->key);
	kzfree(data);
}