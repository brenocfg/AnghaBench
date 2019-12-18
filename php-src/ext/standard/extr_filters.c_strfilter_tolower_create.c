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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  php_stream_filter ;

/* Variables and functions */
 int /*<<< orphan*/ * php_stream_filter_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strfilter_tolower_ops ; 

__attribute__((used)) static php_stream_filter *strfilter_tolower_create(const char *filtername, zval *filterparams, uint8_t persistent)
{
	return php_stream_filter_alloc(&strfilter_tolower_ops, NULL, persistent);
}