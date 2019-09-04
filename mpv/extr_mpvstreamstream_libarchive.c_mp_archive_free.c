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
struct mp_archive {scalar_t__ locale; } ;

/* Variables and functions */
 int /*<<< orphan*/  freelocale (scalar_t__) ; 
 int /*<<< orphan*/  mp_archive_close (struct mp_archive*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_archive*) ; 

void mp_archive_free(struct mp_archive *mpa)
{
    mp_archive_close(mpa);
    if (mpa && mpa->locale)
        freelocale(mpa->locale);
    talloc_free(mpa);
}