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
struct mp_archive {int /*<<< orphan*/ * arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_read_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mp_archive_close(struct mp_archive *mpa)
{
    if (mpa && mpa->arch) {
        archive_read_close(mpa->arch);
        archive_read_free(mpa->arch);
        mpa->arch = NULL;
    }
}