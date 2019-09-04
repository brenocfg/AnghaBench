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
typedef  size_t u32 ;
struct snd_bebob {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (unsigned int*) ; 
 int EIO ; 
 int /*<<< orphan*/  SAFFIREPRO_RATE_NOREBOOT ; 
 unsigned int* rates ; 
 int saffire_read_quad (struct snd_bebob*,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int
saffirepro_both_clk_freq_get(struct snd_bebob *bebob, unsigned int *rate)
{
	u32 id;
	int err;

	err = saffire_read_quad(bebob, SAFFIREPRO_RATE_NOREBOOT, &id);
	if (err < 0)
		goto end;
	if (id >= ARRAY_SIZE(rates))
		err = -EIO;
	else
		*rate = rates[id];
end:
	return err;
}