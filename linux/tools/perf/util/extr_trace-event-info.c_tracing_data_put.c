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
struct tracing_data {int /*<<< orphan*/  temp_file; scalar_t__ temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tracing_data*) ; 
 int record_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

int tracing_data_put(struct tracing_data *tdata)
{
	int err = 0;

	if (tdata->temp) {
		err = record_file(tdata->temp_file, 0);
		unlink(tdata->temp_file);
	}

	free(tdata);
	return err;
}