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
typedef  size_t uint32_t ;
struct ft2_source {scalar_t__ texbuf_y; scalar_t__ texbuf_x; int /*<<< orphan*/ ** cacheglyphs; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_glyphs (struct ft2_source*,char*) ; 
 size_t num_cache_slots ; 

void cache_standard_glyphs(struct ft2_source *srcdata)
{
	for (uint32_t i = 0; i < num_cache_slots; i++) {
		if (srcdata->cacheglyphs[i] != NULL) {
			bfree(srcdata->cacheglyphs[i]);
			srcdata->cacheglyphs[i] = NULL;
		}
	}

	srcdata->texbuf_x = 0;
	srcdata->texbuf_y = 0;

	cache_glyphs(srcdata, L"abcdefghijklmnopqrstuvwxyz"
			      L"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"
			      L"!@#$%^&*()-_=+,<.>/?\\|[]{}`~ \'\"\0");
}