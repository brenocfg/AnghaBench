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
struct snd_ac97 {int dummy; } ;
struct hac_priv {int dummy; } ;

/* Variables and functions */
 struct hac_priv* hac_cpu_data ; 
 unsigned short hac_read_codec_aux (struct hac_priv*,unsigned short) ; 

__attribute__((used)) static unsigned short hac_ac97_read(struct snd_ac97 *ac97,
				    unsigned short reg)
{
	int unit_id = 0 /* ac97->private_data */;
	struct hac_priv *hac = &hac_cpu_data[unit_id];
	return hac_read_codec_aux(hac, reg);
}