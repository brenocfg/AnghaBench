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
typedef  int /*<<< orphan*/  u8 ;
struct xonar_pcm179x {int current_rate; unsigned int dacs; int /*<<< orphan*/  h6; } ;
struct oxygen {struct xonar_pcm179x* model_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCM1796_OS_128 ; 
 int /*<<< orphan*/  PCM1796_OS_64 ; 
 int /*<<< orphan*/  pcm1796_write_cached (struct oxygen*,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_pcm1796_oversampling(struct oxygen *chip)
{
	struct xonar_pcm179x *data = chip->model_data;
	unsigned int i;
	u8 reg;

	if (data->current_rate <= 48000 && !data->h6)
		reg = PCM1796_OS_128;
	else
		reg = PCM1796_OS_64;
	for (i = 0; i < data->dacs; ++i)
		pcm1796_write_cached(chip, i, 20, reg);
}