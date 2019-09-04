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
typedef  size_t uint8 ;
typedef  int /*<<< orphan*/  DATABLOB ;

/* Variables and functions */
 int /*<<< orphan*/ * g_textcache ; 

DATABLOB *
cache_get_text(uint8 cache_id)
{
	DATABLOB *text;

	text = &g_textcache[cache_id];
	return text;
}