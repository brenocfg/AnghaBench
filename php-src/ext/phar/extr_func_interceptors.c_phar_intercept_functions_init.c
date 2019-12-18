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
 int /*<<< orphan*/  PHAR_INTERCEPT (int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  is_link ; 
 int /*<<< orphan*/  is_readable ; 
 int /*<<< orphan*/  is_writable ; 
 int /*<<< orphan*/  lstat ; 
 int /*<<< orphan*/  opendir ; 
 int /*<<< orphan*/  readfile ; 
 int /*<<< orphan*/  stat ; 

void phar_intercept_functions_init(void)
{
	zend_function *orig;

	PHAR_INTERCEPT(fopen);
	PHAR_INTERCEPT(file_get_contents);
	PHAR_INTERCEPT(is_file);
	PHAR_INTERCEPT(is_link);
	PHAR_INTERCEPT(is_dir);
	PHAR_INTERCEPT(opendir);
	PHAR_INTERCEPT(file_exists);
	PHAR_INTERCEPT(fileperms);
	PHAR_INTERCEPT(fileinode);
	PHAR_INTERCEPT(filesize);
	PHAR_INTERCEPT(fileowner);
	PHAR_INTERCEPT(filegroup);
	PHAR_INTERCEPT(fileatime);
	PHAR_INTERCEPT(filemtime);
	PHAR_INTERCEPT(filectime);
	PHAR_INTERCEPT(filetype);
	PHAR_INTERCEPT(is_writable);
	PHAR_INTERCEPT(is_readable);
	PHAR_INTERCEPT(is_executable);
	PHAR_INTERCEPT(lstat);
	PHAR_INTERCEPT(stat);
	PHAR_INTERCEPT(readfile);
	PHAR_G(intercepted) = 0;
}