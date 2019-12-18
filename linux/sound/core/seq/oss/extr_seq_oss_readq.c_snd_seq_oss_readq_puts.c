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
union evrec {int* c; } ;
struct seq_oss_readq {int dummy; } ;
typedef  int /*<<< orphan*/  rec ;

/* Variables and functions */
 int SEQ_MIDIPUTC ; 
 int /*<<< orphan*/  memset (union evrec*,int /*<<< orphan*/ ,int) ; 
 int snd_seq_oss_readq_put_event (struct seq_oss_readq*,union evrec*) ; 

int
snd_seq_oss_readq_puts(struct seq_oss_readq *q, int dev, unsigned char *data, int len)
{
	union evrec rec;
	int result;

	memset(&rec, 0, sizeof(rec));
	rec.c[0] = SEQ_MIDIPUTC;
	rec.c[2] = dev;

	while (len-- > 0) {
		rec.c[1] = *data++;
		result = snd_seq_oss_readq_put_event(q, &rec);
		if (result < 0)
			return result;
	}
	return 0;
}