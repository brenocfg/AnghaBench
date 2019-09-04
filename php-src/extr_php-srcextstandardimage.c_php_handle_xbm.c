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
struct gfxinfo {int dummy; } ;
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  php_get_xbm (int /*<<< orphan*/ *,struct gfxinfo**) ; 

__attribute__((used)) static struct gfxinfo *php_handle_xbm(php_stream * stream)
{
	struct gfxinfo *result;
	php_get_xbm(stream, &result);
	return result;
}