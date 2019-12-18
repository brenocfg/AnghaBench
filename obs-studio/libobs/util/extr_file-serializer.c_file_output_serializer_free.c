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
struct serializer {struct file_output_data* data; } ;
struct file_output_data {struct file_output_data* temp_name; struct file_output_data* file_name; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct file_output_data*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_rename (struct file_output_data*,struct file_output_data*) ; 
 int /*<<< orphan*/  os_unlink (struct file_output_data*) ; 

void file_output_serializer_free(struct serializer *s)
{
	struct file_output_data *out = s->data;

	if (out) {
		fclose(out->file);

		if (out->temp_name) {
			os_unlink(out->file_name);
			os_rename(out->temp_name, out->file_name);
		}

		bfree(out->file_name);
		bfree(out->temp_name);
		bfree(out);
	}
}