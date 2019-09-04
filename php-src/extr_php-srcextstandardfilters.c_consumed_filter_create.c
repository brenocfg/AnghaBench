#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  php_stream_filter_ops ;
typedef  int /*<<< orphan*/  php_stream_filter ;
struct TYPE_4__ {int /*<<< orphan*/  offset; scalar_t__ consumed; int /*<<< orphan*/  persistent; } ;
typedef  TYPE_1__ php_consumed_filter_data ;

/* Variables and functions */
 int /*<<< orphan*/  consumed_filter_ops ; 
 TYPE_1__* pecalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * php_stream_filter_alloc (int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static php_stream_filter *consumed_filter_create(const char *filtername, zval *filterparams, uint8_t persistent)
{
	const php_stream_filter_ops *fops = NULL;
	php_consumed_filter_data *data;

	if (strcasecmp(filtername, "consumed")) {
		return NULL;
	}

	/* Create this filter */
	data = pecalloc(1, sizeof(php_consumed_filter_data), persistent);
	data->persistent = persistent;
	data->consumed = 0;
	data->offset = ~0;
	fops = &consumed_filter_ops;

	return php_stream_filter_alloc(fops, data, persistent);
}