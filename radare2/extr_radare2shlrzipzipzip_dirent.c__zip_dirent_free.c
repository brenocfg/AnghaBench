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
struct zip_dirent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _zip_dirent_finalize (struct zip_dirent*) ; 
 int /*<<< orphan*/  free (struct zip_dirent*) ; 

void
_zip_dirent_free(struct zip_dirent *zde)
{
    if (zde == NULL)
	return;

    _zip_dirent_finalize(zde);
    free(zde);
}