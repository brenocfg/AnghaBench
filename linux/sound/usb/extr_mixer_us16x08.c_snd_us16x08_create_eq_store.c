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
struct snd_us16x08_eq_store {int*** val; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SND_US16X08_EQ_HIGHFREQ_BIAS ; 
 int SND_US16X08_ID_EQ_BAND_COUNT ; 
 int SND_US16X08_MAX_CHANNELS ; 
 struct snd_us16x08_eq_store* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_us16x08_eq_store *snd_us16x08_create_eq_store(void)
{
	int i, b_idx;
	struct snd_us16x08_eq_store *tmp;

	tmp = kmalloc(sizeof(*tmp), GFP_KERNEL);
	if (!tmp)
		return NULL;

	for (i = 0; i < SND_US16X08_MAX_CHANNELS; i++) {
		for (b_idx = 0; b_idx < SND_US16X08_ID_EQ_BAND_COUNT; b_idx++) {
			tmp->val[b_idx][0][i] = 0x0c;
			tmp->val[b_idx][3][i] = 0x00;
			switch (b_idx) {
			case 0: /* EQ Low */
				tmp->val[b_idx][1][i] = 0x05;
				tmp->val[b_idx][2][i] = 0xff;
				break;
			case 1: /* EQ Mid low */
				tmp->val[b_idx][1][i] = 0x0e;
				tmp->val[b_idx][2][i] = 0x02;
				break;
			case 2: /* EQ Mid High */
				tmp->val[b_idx][1][i] = 0x1b;
				tmp->val[b_idx][2][i] = 0x02;
				break;
			case 3: /* EQ High */
				tmp->val[b_idx][1][i] = 0x2f
					- SND_US16X08_EQ_HIGHFREQ_BIAS;
				tmp->val[b_idx][2][i] = 0xff;
				break;
			}
		}
	}
	return tmp;
}