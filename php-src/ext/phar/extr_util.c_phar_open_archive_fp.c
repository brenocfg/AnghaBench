#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fname; } ;
typedef  TYPE_1__ phar_archive_data ;

/* Variables and functions */
 int FAILURE ; 
 int IGNORE_URL ; 
 int STREAM_MUST_SEEK ; 
 int SUCCESS ; 
 scalar_t__ phar_get_pharfp (TYPE_1__*) ; 
 int /*<<< orphan*/  phar_set_pharfp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ php_check_open_basedir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_open_wrapper (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

int phar_open_archive_fp(phar_archive_data *phar) /* {{{ */
{
	if (phar_get_pharfp(phar)) {
		return SUCCESS;
	}

	if (php_check_open_basedir(phar->fname)) {
		return FAILURE;
	}

	phar_set_pharfp(phar, php_stream_open_wrapper(phar->fname, "rb", IGNORE_URL|STREAM_MUST_SEEK|0, NULL));

	if (!phar_get_pharfp(phar)) {
		return FAILURE;
	}

	return SUCCESS;
}