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
typedef  int /*<<< orphan*/  zend_string ;

/* Variables and functions */
 int /*<<< orphan*/ * phar_find_in_include_path (char*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_string *phar_resolve_path(const char *filename, size_t filename_len)
{
	return phar_find_in_include_path((char *) filename, filename_len, NULL);
}