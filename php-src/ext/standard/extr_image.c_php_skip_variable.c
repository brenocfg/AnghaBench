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
typedef  int zend_off_t ;
typedef  int /*<<< orphan*/  zend_long ;
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ php_read2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_skip_variable(php_stream * stream)
{
	zend_off_t length = ((unsigned int)php_read2(stream));

	if (length < 2)	{
		return 0;
	}
	length = length - 2;
	php_stream_seek(stream, (zend_long)length, SEEK_CUR);
	return 1;
}