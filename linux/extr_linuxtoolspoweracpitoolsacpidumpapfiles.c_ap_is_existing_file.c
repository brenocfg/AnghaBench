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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char getchar () ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int ap_is_existing_file(char *pathname)
{
#if !defined(_GNU_EFI) && !defined(_EDK2_EFI)
	struct stat stat_info;

	if (!stat(pathname, &stat_info)) {
		fprintf(stderr,
			"Target path already exists, overwrite? [y|n] ");

		if (getchar() != 'y') {
			return (-1);
		}
	}
#endif

	return 0;
}