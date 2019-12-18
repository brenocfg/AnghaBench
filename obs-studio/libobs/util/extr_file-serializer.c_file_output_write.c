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
struct file_output_data {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 size_t fwrite (void const*,int,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t file_output_write(void *sdata, const void *data, size_t size)
{
	struct file_output_data *out = sdata;
	return fwrite(data, 1, size, out->file);
}