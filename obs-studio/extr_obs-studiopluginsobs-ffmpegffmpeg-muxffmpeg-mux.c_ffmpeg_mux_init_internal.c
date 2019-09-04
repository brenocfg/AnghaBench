#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct header {int dummy; } ;
struct TYPE_2__ {int tracks; } ;
struct ffmpeg_mux {TYPE_1__ params; int /*<<< orphan*/  audio_header; int /*<<< orphan*/  audio; } ;

/* Variables and functions */
 int FFM_ERROR ; 
 int /*<<< orphan*/  av_register_all () ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 int /*<<< orphan*/  ffmpeg_mux_get_extra_data (struct ffmpeg_mux*) ; 
 int ffmpeg_mux_init_context (struct ffmpeg_mux*) ; 
 int /*<<< orphan*/  init_params (int*,char***,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ffmpeg_mux_init_internal(struct ffmpeg_mux *ffm, int argc,
		char *argv[])
{
	argc--;
	argv++;
	if (!init_params(&argc, &argv, &ffm->params, &ffm->audio))
		return FFM_ERROR;

	if (ffm->params.tracks) {
		ffm->audio_header =
			calloc(1, sizeof(struct header) * ffm->params.tracks);
	}

	av_register_all();

	if (!ffmpeg_mux_get_extra_data(ffm))
		return FFM_ERROR;

	/* ffmpeg does not have a way of telling what's supported
	 * for a given output format, so we try each possibility */
	return ffmpeg_mux_init_context(ffm);
}