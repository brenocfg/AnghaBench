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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  os_ftelli64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t file_output_get_pos(void *sdata)
{
	struct file_output_data *out = sdata;
	return os_ftelli64(out->file);
}