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
struct snd_compr_stream {int dummy; } ;
struct snd_compr_caps {int num_codecs; int /*<<< orphan*/ * codecs; int /*<<< orphan*/  max_fragments; int /*<<< orphan*/  min_fragments; int /*<<< orphan*/  max_fragment_size; int /*<<< orphan*/  min_fragment_size; int /*<<< orphan*/  direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPR_PLAYBACK_MAX_FRAGMENT_SIZE ; 
 int /*<<< orphan*/  COMPR_PLAYBACK_MAX_NUM_FRAGMENTS ; 
 int /*<<< orphan*/  COMPR_PLAYBACK_MIN_FRAGMENT_SIZE ; 
 int /*<<< orphan*/  COMPR_PLAYBACK_MIN_NUM_FRAGMENTS ; 
 int /*<<< orphan*/  SND_AUDIOCODEC_MP3 ; 
 int /*<<< orphan*/  SND_COMPRESS_PLAYBACK ; 

__attribute__((used)) static int q6asm_dai_compr_get_caps(struct snd_compr_stream *stream,
				    struct snd_compr_caps *caps)
{
	caps->direction = SND_COMPRESS_PLAYBACK;
	caps->min_fragment_size = COMPR_PLAYBACK_MIN_FRAGMENT_SIZE;
	caps->max_fragment_size = COMPR_PLAYBACK_MAX_FRAGMENT_SIZE;
	caps->min_fragments = COMPR_PLAYBACK_MIN_NUM_FRAGMENTS;
	caps->max_fragments = COMPR_PLAYBACK_MAX_NUM_FRAGMENTS;
	caps->num_codecs = 1;
	caps->codecs[0] = SND_AUDIOCODEC_MP3;

	return 0;
}