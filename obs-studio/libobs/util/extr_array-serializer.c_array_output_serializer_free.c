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
struct array_output_data {int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 

void array_output_serializer_free(struct array_output_data *data)
{
	da_free(data->bytes);
}