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
struct file {struct coda_file_info* private_data; } ;
struct coda_file_info {scalar_t__ cfi_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CODA_MAGIC ; 

struct coda_file_info *coda_ftoc(struct file *file)
{
	struct coda_file_info *cfi = file->private_data;

	BUG_ON(!cfi || cfi->cfi_magic != CODA_MAGIC);

	return cfi;

}