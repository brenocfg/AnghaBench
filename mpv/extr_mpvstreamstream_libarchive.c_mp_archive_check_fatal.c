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
struct mp_archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  MP_FATAL (struct mp_archive*,char*) ; 
 int /*<<< orphan*/  mp_archive_close (struct mp_archive*) ; 

__attribute__((used)) static bool mp_archive_check_fatal(struct mp_archive *mpa, int r)
{
    if (r > ARCHIVE_FATAL)
        return false;
    MP_FATAL(mpa, "fatal error received - closing archive\n");
    mp_archive_close(mpa);
    return true;
}