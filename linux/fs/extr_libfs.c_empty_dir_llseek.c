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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  generic_file_llseek_size (struct file*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static loff_t empty_dir_llseek(struct file *file, loff_t offset, int whence)
{
	/* An empty directory has two entries . and .. at offsets 0 and 1 */
	return generic_file_llseek_size(file, offset, whence, 2, 2);
}