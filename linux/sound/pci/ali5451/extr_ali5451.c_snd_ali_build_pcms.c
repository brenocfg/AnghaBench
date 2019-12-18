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
struct snd_ali {int num_of_codecs; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ali_pcms ; 
 int snd_ali_pcm (struct snd_ali*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ali_build_pcms(struct snd_ali *codec)
{
	int i, err;
	for (i = 0; i < codec->num_of_codecs && i < ARRAY_SIZE(ali_pcms); i++) {
		err = snd_ali_pcm(codec, i, &ali_pcms[i]);
		if (err < 0)
			return err;
	}
	return 0;
}