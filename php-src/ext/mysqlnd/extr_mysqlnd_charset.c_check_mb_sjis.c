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
 scalar_t__ valid_sjis_head (int /*<<< orphan*/ ) ; 
 scalar_t__ valid_sjis_tail (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int check_mb_sjis(const char * const start, const char * const end)
{
	return (valid_sjis_head((zend_uchar)start[0]) && (end - start) > 1 && valid_sjis_tail((zend_uchar)start[1])) ? 2 : 0;
}