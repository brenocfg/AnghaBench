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
struct snd_soc_dai {struct g12a_tohdmitx_input* playback_dma_data; } ;
struct g12a_tohdmitx_input {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct g12a_tohdmitx_input* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int g12a_tohdmitx_input_probe(struct snd_soc_dai *dai)
{
	struct g12a_tohdmitx_input *data;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	dai->playback_dma_data = data;
	return 0;
}