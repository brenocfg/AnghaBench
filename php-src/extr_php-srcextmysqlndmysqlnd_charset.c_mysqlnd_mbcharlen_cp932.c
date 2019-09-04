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
typedef  int /*<<< orphan*/  zend_uchar ;

/* Variables and functions */
 scalar_t__ valid_cp932head (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int mysqlnd_mbcharlen_cp932(const unsigned int cp932)
{
	return (valid_cp932head((zend_uchar)cp932)) ? 2 : 1;
}