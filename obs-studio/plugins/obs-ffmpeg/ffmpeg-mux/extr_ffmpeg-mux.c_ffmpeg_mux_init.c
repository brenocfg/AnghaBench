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
struct ffmpeg_mux {int initialized; } ;

/* Variables and functions */
 int FFM_SUCCESS ; 
 int /*<<< orphan*/  ffmpeg_mux_free (struct ffmpeg_mux*) ; 
 int ffmpeg_mux_init_internal (struct ffmpeg_mux*,int,char**) ; 

__attribute__((used)) static int ffmpeg_mux_init(struct ffmpeg_mux *ffm, int argc, char *argv[])
{
	int ret = ffmpeg_mux_init_internal(ffm, argc, argv);
	if (ret != FFM_SUCCESS) {
		ffmpeg_mux_free(ffm);
		return ret;
	}

	ffm->initialized = true;
	return ret;
}