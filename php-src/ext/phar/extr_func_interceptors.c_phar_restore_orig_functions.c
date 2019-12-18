#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  orig_stat; int /*<<< orphan*/  orig_readfile; int /*<<< orphan*/  orig_lstat; int /*<<< orphan*/  orig_is_executable; int /*<<< orphan*/  orig_is_readable; int /*<<< orphan*/  orig_is_writable; int /*<<< orphan*/  orig_filetype; int /*<<< orphan*/  orig_filectime; int /*<<< orphan*/  orig_filemtime; int /*<<< orphan*/  orig_fileatime; int /*<<< orphan*/  orig_filegroup; int /*<<< orphan*/  orig_fileowner; int /*<<< orphan*/  orig_filesize; int /*<<< orphan*/  orig_fileinode; int /*<<< orphan*/  orig_fileperms; int /*<<< orphan*/  orig_file_exists; int /*<<< orphan*/  orig_opendir; int /*<<< orphan*/  orig_is_dir; int /*<<< orphan*/  orig_is_link; int /*<<< orphan*/  orig_is_file; int /*<<< orphan*/  orig_file_get_contents; int /*<<< orphan*/  orig_fopen; } ;
typedef  int /*<<< orphan*/  PHAR_G ;

/* Variables and functions */
 TYPE_1__ phar_orig_functions ; 

void phar_restore_orig_functions(void) /* {{{ */
{
	PHAR_G(orig_fopen)             = phar_orig_functions.orig_fopen;
	PHAR_G(orig_file_get_contents) = phar_orig_functions.orig_file_get_contents;
	PHAR_G(orig_is_file)           = phar_orig_functions.orig_is_file;
	PHAR_G(orig_is_link)           = phar_orig_functions.orig_is_link;
	PHAR_G(orig_is_dir)            = phar_orig_functions.orig_is_dir;
	PHAR_G(orig_opendir)           = phar_orig_functions.orig_opendir;
	PHAR_G(orig_file_exists)       = phar_orig_functions.orig_file_exists;
	PHAR_G(orig_fileperms)         = phar_orig_functions.orig_fileperms;
	PHAR_G(orig_fileinode)         = phar_orig_functions.orig_fileinode;
	PHAR_G(orig_filesize)          = phar_orig_functions.orig_filesize;
	PHAR_G(orig_fileowner)         = phar_orig_functions.orig_fileowner;
	PHAR_G(orig_filegroup)         = phar_orig_functions.orig_filegroup;
	PHAR_G(orig_fileatime)         = phar_orig_functions.orig_fileatime;
	PHAR_G(orig_filemtime)         = phar_orig_functions.orig_filemtime;
	PHAR_G(orig_filectime)         = phar_orig_functions.orig_filectime;
	PHAR_G(orig_filetype)          = phar_orig_functions.orig_filetype;
	PHAR_G(orig_is_writable)       = phar_orig_functions.orig_is_writable;
	PHAR_G(orig_is_readable)       = phar_orig_functions.orig_is_readable;
	PHAR_G(orig_is_executable)     = phar_orig_functions.orig_is_executable;
	PHAR_G(orig_lstat)             = phar_orig_functions.orig_lstat;
	PHAR_G(orig_readfile)          = phar_orig_functions.orig_readfile;
	PHAR_G(orig_stat)              = phar_orig_functions.orig_stat;
}