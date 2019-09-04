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
struct snd_compr_caps {int /*<<< orphan*/ * codecs; int /*<<< orphan*/  max_fragments; int /*<<< orphan*/  min_fragments; int /*<<< orphan*/  max_fragment_size; int /*<<< orphan*/  min_fragment_size; int /*<<< orphan*/  num_codecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_FRAGMENT ; 
 int /*<<< orphan*/  MAX_FRAGMENT_SIZE ; 
 int /*<<< orphan*/  MIN_FRAGMENT ; 
 int /*<<< orphan*/  MIN_FRAGMENT_SIZE ; 
 int /*<<< orphan*/  NUM_CODEC ; 
 int /*<<< orphan*/  SND_AUDIOCODEC_AAC ; 
 int /*<<< orphan*/  SND_AUDIOCODEC_MP3 ; 

__attribute__((used)) static int sst_cdev_caps(struct snd_compr_caps *caps)
{
	caps->num_codecs = NUM_CODEC;
	caps->min_fragment_size = MIN_FRAGMENT_SIZE;  /* 50KB */
	caps->max_fragment_size = MAX_FRAGMENT_SIZE;  /* 1024KB */
	caps->min_fragments = MIN_FRAGMENT;
	caps->max_fragments = MAX_FRAGMENT;
	caps->codecs[0] = SND_AUDIOCODEC_MP3;
	caps->codecs[1] = SND_AUDIOCODEC_AAC;
	return 0;
}