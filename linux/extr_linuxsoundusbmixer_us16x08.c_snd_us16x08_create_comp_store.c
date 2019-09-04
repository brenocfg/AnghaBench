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
struct snd_us16x08_comp_store {int** val; } ;

/* Variables and functions */
 size_t COMP_STORE_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SND_US16X08_ID_COMP_ATTACK ; 
 int /*<<< orphan*/  SND_US16X08_ID_COMP_GAIN ; 
 int /*<<< orphan*/  SND_US16X08_ID_COMP_RATIO ; 
 int /*<<< orphan*/  SND_US16X08_ID_COMP_RELEASE ; 
 int /*<<< orphan*/  SND_US16X08_ID_COMP_SWITCH ; 
 int /*<<< orphan*/  SND_US16X08_ID_COMP_THRESHOLD ; 
 int SND_US16X08_MAX_CHANNELS ; 
 struct snd_us16x08_comp_store* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_us16x08_comp_store *snd_us16x08_create_comp_store(void)
{
	int i;
	struct snd_us16x08_comp_store *tmp;

	tmp = kmalloc(sizeof(*tmp), GFP_KERNEL);
	if (!tmp)
		return NULL;

	for (i = 0; i < SND_US16X08_MAX_CHANNELS; i++) {
		tmp->val[COMP_STORE_IDX(SND_US16X08_ID_COMP_THRESHOLD)][i]
			= 0x20;
		tmp->val[COMP_STORE_IDX(SND_US16X08_ID_COMP_RATIO)][i] = 0x00;
		tmp->val[COMP_STORE_IDX(SND_US16X08_ID_COMP_GAIN)][i] = 0x00;
		tmp->val[COMP_STORE_IDX(SND_US16X08_ID_COMP_SWITCH)][i] = 0x00;
		tmp->val[COMP_STORE_IDX(SND_US16X08_ID_COMP_ATTACK)][i] = 0x00;
		tmp->val[COMP_STORE_IDX(SND_US16X08_ID_COMP_RELEASE)][i] = 0x00;
	}
	return tmp;
}