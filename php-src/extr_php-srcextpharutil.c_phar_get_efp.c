#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_8__ {scalar_t__ fp_type; int /*<<< orphan*/ * fp; int /*<<< orphan*/  tmp; int /*<<< orphan*/  phar; scalar_t__ link; } ;
typedef  TYPE_1__ phar_entry_info ;

/* Variables and functions */
 scalar_t__ PHAR_FP ; 
 scalar_t__ PHAR_MOD ; 
 scalar_t__ PHAR_UFP ; 
 int STREAM_MUST_SEEK ; 
 int /*<<< orphan*/ * phar_get_entrypfp (TYPE_1__*) ; 
 int /*<<< orphan*/ * phar_get_entrypufp (TYPE_1__*) ; 
 scalar_t__ phar_get_fp_type (TYPE_1__*) ; 
 TYPE_1__* phar_get_link_source (TYPE_1__*) ; 
 int /*<<< orphan*/  phar_open_archive_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * php_stream_open_wrapper (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

php_stream *phar_get_efp(phar_entry_info *entry, int follow_links) /* {{{ */
{
	if (follow_links && entry->link) {
		phar_entry_info *link_entry = phar_get_link_source(entry);

		if (link_entry && link_entry != entry) {
			return phar_get_efp(link_entry, 1);
		}
	}

	if (phar_get_fp_type(entry) == PHAR_FP) {
		if (!phar_get_entrypfp(entry)) {
			/* re-open just in time for cases where our refcount reached 0 on the phar archive */
			phar_open_archive_fp(entry->phar);
		}
		return phar_get_entrypfp(entry);
	} else if (phar_get_fp_type(entry) == PHAR_UFP) {
		return phar_get_entrypufp(entry);
	} else if (entry->fp_type == PHAR_MOD) {
		return entry->fp;
	} else {
		/* temporary manifest entry */
		if (!entry->fp) {
			entry->fp = php_stream_open_wrapper(entry->tmp, "rb", STREAM_MUST_SEEK|0, NULL);
		}
		return entry->fp;
	}
}