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

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * fis_desc ; 
 int /*<<< orphan*/  fis_erasesize ; 
 int fis_fd ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fis_close(void)
{
	if (fis_desc)
		munmap(fis_desc, fis_erasesize);

	if (fis_fd >= 0)
		close(fis_fd);

	fis_fd = -1;
	fis_desc = NULL;
}