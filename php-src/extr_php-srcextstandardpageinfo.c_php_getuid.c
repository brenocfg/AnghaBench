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
typedef  int /*<<< orphan*/  zend_long ;

/* Variables and functions */
 int /*<<< orphan*/  BG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_uid ; 
 int /*<<< orphan*/  php_statpage () ; 

zend_long php_getuid(void)
{
	php_statpage();
	return (BG(page_uid));
}