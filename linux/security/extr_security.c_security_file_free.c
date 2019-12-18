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
struct file {int /*<<< orphan*/ * f_security; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_void_hook (int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  file_free_security ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  lsm_file_cache ; 

void security_file_free(struct file *file)
{
	void *blob;

	call_void_hook(file_free_security, file);

	blob = file->f_security;
	if (blob) {
		file->f_security = NULL;
		kmem_cache_free(lsm_file_cache, blob);
	}
}