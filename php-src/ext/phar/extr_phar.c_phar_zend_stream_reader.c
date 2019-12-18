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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  phar_archive_data ;

/* Variables and functions */
 int /*<<< orphan*/  phar_get_pharfp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_read (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static ssize_t phar_zend_stream_reader(void *handle, char *buf, size_t len) /* {{{ */
{
	return php_stream_read(phar_get_pharfp((phar_archive_data*)handle), buf, len);
}