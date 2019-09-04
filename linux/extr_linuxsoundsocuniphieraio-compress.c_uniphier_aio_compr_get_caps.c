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
struct snd_compr_caps {int num_codecs; int /*<<< orphan*/ * codecs; int /*<<< orphan*/  max_fragments; int /*<<< orphan*/  min_fragments; int /*<<< orphan*/  max_fragment_size; int /*<<< orphan*/  min_fragment_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_MAX_FRAGMENT ; 
 int /*<<< orphan*/  AUD_MAX_FRAGMENT_SIZE ; 
 int /*<<< orphan*/  AUD_MIN_FRAGMENT ; 
 int /*<<< orphan*/  AUD_MIN_FRAGMENT_SIZE ; 
 int /*<<< orphan*/  SND_AUDIOCODEC_IEC61937 ; 

__attribute__((used)) static int uniphier_aio_compr_get_caps(struct snd_compr_stream *cstream,
				       struct snd_compr_caps *caps)
{
	caps->num_codecs = 1;
	caps->min_fragment_size = AUD_MIN_FRAGMENT_SIZE;
	caps->max_fragment_size = AUD_MAX_FRAGMENT_SIZE;
	caps->min_fragments = AUD_MIN_FRAGMENT;
	caps->max_fragments = AUD_MAX_FRAGMENT;
	caps->codecs[0] = SND_AUDIOCODEC_IEC61937;

	return 0;
}