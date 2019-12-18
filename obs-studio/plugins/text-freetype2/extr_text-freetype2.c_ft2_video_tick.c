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
typedef  scalar_t__ time_t ;
struct ft2_source {int last_checked; int update_file; scalar_t__ m_timestamp; int /*<<< orphan*/  text; int /*<<< orphan*/  text_file; scalar_t__ log_mode; int /*<<< orphan*/  from_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (float) ; 
 int /*<<< orphan*/  cache_glyphs (struct ft2_source*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_modified_timestamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_text_from_file (struct ft2_source*,int /*<<< orphan*/ ) ; 
 int os_gettime_ns () ; 
 int /*<<< orphan*/  read_from_end (struct ft2_source*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_up_vertex_buffer (struct ft2_source*) ; 

__attribute__((used)) static void ft2_video_tick(void *data, float seconds)
{
	struct ft2_source *srcdata = data;
	if (srcdata == NULL)
		return;
	if (!srcdata->from_file || !srcdata->text_file)
		return;

	if (os_gettime_ns() - srcdata->last_checked >= 1000000000) {
		time_t t = get_modified_timestamp(srcdata->text_file);
		srcdata->last_checked = os_gettime_ns();

		if (srcdata->update_file) {
			if (srcdata->log_mode)
				read_from_end(srcdata, srcdata->text_file);
			else
				load_text_from_file(srcdata,
						    srcdata->text_file);
			cache_glyphs(srcdata, srcdata->text);
			set_up_vertex_buffer(srcdata);
			srcdata->update_file = false;
		}

		if (srcdata->m_timestamp != t) {
			srcdata->m_timestamp = t;
			srcdata->update_file = true;
		}
	}

	UNUSED_PARAMETER(seconds);
}