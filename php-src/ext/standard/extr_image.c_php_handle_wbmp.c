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
 scalar_t__ ecalloc (int,int) ; 
 int /*<<< orphan*/  efree (struct gfxinfo*) ; 
 int /*<<< orphan*/  php_get_wbmp (int /*<<< orphan*/ *,struct gfxinfo**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct gfxinfo *php_handle_wbmp(php_stream * stream)
{
	struct gfxinfo *result = (struct gfxinfo *) ecalloc(1, sizeof(struct gfxinfo));

	if (!php_get_wbmp(stream, &result, 0)) {
		efree(result);
		return NULL;
	}

	return result;
}