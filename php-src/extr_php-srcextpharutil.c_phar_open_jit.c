#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ phar_entry_info ;
struct TYPE_9__ {int /*<<< orphan*/  fname; } ;
typedef  TYPE_2__ phar_archive_data ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ phar_open_entry_fp (TYPE_1__*,char**,int) ; 
 int phar_seek_efp (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spprintf (char**,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

phar_entry_info * phar_open_jit(phar_archive_data *phar, phar_entry_info *entry, char **error) /* {{{ */
{
	if (error) {
		*error = NULL;
	}
	/* seek to start of internal file and read it */
	if (FAILURE == phar_open_entry_fp(entry, error, 1)) {
		return NULL;
	}
	if (-1 == phar_seek_efp(entry, 0, SEEK_SET, 0, 1)) {
		spprintf(error, 4096, "phar error: cannot seek to start of file \"%s\" in phar \"%s\"", entry->filename, phar->fname);
		return NULL;
	}
	return entry;
}