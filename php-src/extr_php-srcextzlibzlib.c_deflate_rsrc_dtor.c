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
typedef  int /*<<< orphan*/  zend_resource ;
typedef  int /*<<< orphan*/  z_stream ;

/* Variables and functions */
 int /*<<< orphan*/  deflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le_deflate ; 
 int /*<<< orphan*/ * zend_fetch_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void deflate_rsrc_dtor(zend_resource *res)
{
	z_stream *ctx = zend_fetch_resource(res, NULL, le_deflate);
	deflateEnd(ctx);
	efree(ctx);
}