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
struct lola_pcm {int num_streams; int /*<<< orphan*/ * streams; } ;
struct lola {struct lola_pcm* pcm; } ;

/* Variables and functions */
 int lola_init_stream (struct lola*,int /*<<< orphan*/ *,int,int,int) ; 

int lola_init_pcm(struct lola *chip, int dir, int *nidp)
{
	struct lola_pcm *pcm = &chip->pcm[dir];
	int i, nid, err;

	nid = *nidp;
	for (i = 0; i < pcm->num_streams; i++, nid++) {
		err = lola_init_stream(chip, &pcm->streams[i], i, nid, dir);
		if (err < 0)
			return err;
	}
	*nidp = nid;
	return 0;
}