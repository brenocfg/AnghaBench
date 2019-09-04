#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  persistent; struct TYPE_6__* outbuf; struct TYPE_6__* inbuf; int /*<<< orphan*/  strm; } ;
typedef  TYPE_1__ php_zlib_filter_data ;
struct TYPE_7__ {int /*<<< orphan*/  abstract; } ;
typedef  TYPE_2__ php_stream_filter ;

/* Variables and functions */
 TYPE_1__* Z_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pefree (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void php_zlib_deflate_dtor(php_stream_filter *thisfilter)
{
	if (thisfilter && Z_PTR(thisfilter->abstract)) {
		php_zlib_filter_data *data = Z_PTR(thisfilter->abstract);
		deflateEnd(&(data->strm));
		pefree(data->inbuf, data->persistent);
		pefree(data->outbuf, data->persistent);
		pefree(data, data->persistent);
	}
}