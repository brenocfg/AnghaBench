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
typedef  int /*<<< orphan*/  zend_function ;
typedef  int /*<<< orphan*/  PHAR_G ;

/* Variables and functions */
 int /*<<< orphan*/  PHAR_RELEASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_exists ; 
 int /*<<< orphan*/  file_get_contents ; 
 int /*<<< orphan*/  fileatime ; 
 int /*<<< orphan*/  filectime ; 
 int /*<<< orphan*/  filegroup ; 
 int /*<<< orphan*/  fileinode ; 
 int /*<<< orphan*/  filemtime ; 
 int /*<<< orphan*/  fileowner ; 
 int /*<<< orphan*/  fileperms ; 
 int /*<<< orphan*/  filesize ; 
 int /*<<< orphan*/  filetype ; 
 int /*<<< orphan*/  fopen ; 
 int /*<<< orphan*/  is_dir ; 
 int /*<<< orphan*/  is_executable ; 
 int /*<<< orphan*/  is_file ; 
 int /*<<< orphan*/  is_readable ; 
 int /*<<< orphan*/  is_writable ; 
 int /*<<< orphan*/  lstat ; 
 int /*<<< orphan*/  opendir ; 
 int /*<<< orphan*/  readfile ; 
 int /*<<< orphan*/  stat ; 

void phar_intercept_functions_shutdown(void)
{
	zend_function *orig;

	PHAR_RELEASE(fopen);
	PHAR_RELEASE(file_get_contents);
	PHAR_RELEASE(is_file);
	PHAR_RELEASE(is_dir);
	PHAR_RELEASE(opendir);
	PHAR_RELEASE(file_exists);
	PHAR_RELEASE(fileperms);
	PHAR_RELEASE(fileinode);
	PHAR_RELEASE(filesize);
	PHAR_RELEASE(fileowner);
	PHAR_RELEASE(filegroup);
	PHAR_RELEASE(fileatime);
	PHAR_RELEASE(filemtime);
	PHAR_RELEASE(filectime);
	PHAR_RELEASE(filetype);
	PHAR_RELEASE(is_writable);
	PHAR_RELEASE(is_readable);
	PHAR_RELEASE(is_executable);
	PHAR_RELEASE(lstat);
	PHAR_RELEASE(stat);
	PHAR_RELEASE(readfile);
	PHAR_G(intercepted) = 0;
}