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
typedef  int u32 ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int FSs (int) ; 
 int /*<<< orphan*/  MD_CTL2 ; 
 int PSs (int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ak4642_set_mcko(struct snd_soc_component *component,
			   u32 frequency)
{
	static const u32 fs_list[] = {
		[0] = 8000,
		[1] = 12000,
		[2] = 16000,
		[3] = 24000,
		[4] = 7350,
		[5] = 11025,
		[6] = 14700,
		[7] = 22050,
		[10] = 32000,
		[11] = 48000,
		[14] = 29400,
		[15] = 44100,
	};
	static const u32 ps_list[] = {
		[0] = 256,
		[1] = 128,
		[2] = 64,
		[3] = 32
	};
	int ps, fs;

	for (ps = 0; ps < ARRAY_SIZE(ps_list); ps++) {
		for (fs = 0; fs < ARRAY_SIZE(fs_list); fs++) {
			if (frequency == ps_list[ps] * fs_list[fs]) {
				snd_soc_component_write(component, MD_CTL2,
					      PSs(ps) | FSs(fs));
				return 0;
			}
		}
	}

	return 0;
}