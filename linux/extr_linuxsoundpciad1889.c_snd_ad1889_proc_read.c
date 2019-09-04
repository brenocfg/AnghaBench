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
typedef  int u16 ;
struct snd_info_entry {struct snd_ad1889* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct snd_ad1889 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD_DS_RAMC ; 
 int AD_DS_RAMC_ACRQ ; 
 int AD_DS_RAMC_AD16 ; 
 int AD_DS_RAMC_ADEN ; 
 int AD_DS_RAMC_ADST ; 
 int AD_DS_RAMC_REEN ; 
 int AD_DS_RAMC_RERQ ; 
 int /*<<< orphan*/  AD_DS_RES ; 
 int /*<<< orphan*/  AD_DS_WADA ; 
 int AD_DS_WADA_LWAA ; 
 int AD_DS_WADA_LWAM ; 
 int AD_DS_WADA_RWAA ; 
 int AD_DS_WADA_RWAM ; 
 int /*<<< orphan*/  AD_DS_WAS ; 
 int /*<<< orphan*/  AD_DS_WSMC ; 
 int AD_DS_WSMC_SYEN ; 
 int AD_DS_WSMC_SYRQ ; 
 int AD_DS_WSMC_WA16 ; 
 int AD_DS_WSMC_WAEN ; 
 int AD_DS_WSMC_WARQ ; 
 int AD_DS_WSMC_WAST ; 
 int ad1889_readw (struct snd_ad1889*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void
snd_ad1889_proc_read(struct snd_info_entry *entry, struct snd_info_buffer *buffer)
{
	struct snd_ad1889 *chip = entry->private_data;
	u16 reg;
	int tmp;

	reg = ad1889_readw(chip, AD_DS_WSMC);
	snd_iprintf(buffer, "Wave output: %s\n",
			(reg & AD_DS_WSMC_WAEN) ? "enabled" : "disabled");
	snd_iprintf(buffer, "Wave Channels: %s\n",
			(reg & AD_DS_WSMC_WAST) ? "stereo" : "mono");
	snd_iprintf(buffer, "Wave Quality: %d-bit linear\n",
			(reg & AD_DS_WSMC_WA16) ? 16 : 8);
	
	/* WARQ is at offset 12 */
	tmp = (reg & AD_DS_WSMC_WARQ) ?
		((((reg & AD_DS_WSMC_WARQ) >> 12) & 0x01) ? 12 : 18) : 4;
	tmp /= (reg & AD_DS_WSMC_WAST) ? 2 : 1;
	
	snd_iprintf(buffer, "Wave FIFO: %d %s words\n\n", tmp,
			(reg & AD_DS_WSMC_WAST) ? "stereo" : "mono");
				
	
	snd_iprintf(buffer, "Synthesis output: %s\n",
			reg & AD_DS_WSMC_SYEN ? "enabled" : "disabled");
	
	/* SYRQ is at offset 4 */
	tmp = (reg & AD_DS_WSMC_SYRQ) ?
		((((reg & AD_DS_WSMC_SYRQ) >> 4) & 0x01) ? 12 : 18) : 4;
	tmp /= (reg & AD_DS_WSMC_WAST) ? 2 : 1;
	
	snd_iprintf(buffer, "Synthesis FIFO: %d %s words\n\n", tmp,
			(reg & AD_DS_WSMC_WAST) ? "stereo" : "mono");

	reg = ad1889_readw(chip, AD_DS_RAMC);
	snd_iprintf(buffer, "ADC input: %s\n",
			(reg & AD_DS_RAMC_ADEN) ? "enabled" : "disabled");
	snd_iprintf(buffer, "ADC Channels: %s\n",
			(reg & AD_DS_RAMC_ADST) ? "stereo" : "mono");
	snd_iprintf(buffer, "ADC Quality: %d-bit linear\n",
			(reg & AD_DS_RAMC_AD16) ? 16 : 8);
	
	/* ACRQ is at offset 4 */
	tmp = (reg & AD_DS_RAMC_ACRQ) ?
		((((reg & AD_DS_RAMC_ACRQ) >> 4) & 0x01) ? 12 : 18) : 4;
	tmp /= (reg & AD_DS_RAMC_ADST) ? 2 : 1;
	
	snd_iprintf(buffer, "ADC FIFO: %d %s words\n\n", tmp,
			(reg & AD_DS_RAMC_ADST) ? "stereo" : "mono");
	
	snd_iprintf(buffer, "Resampler input: %s\n",
			reg & AD_DS_RAMC_REEN ? "enabled" : "disabled");
			
	/* RERQ is at offset 12 */
	tmp = (reg & AD_DS_RAMC_RERQ) ?
		((((reg & AD_DS_RAMC_RERQ) >> 12) & 0x01) ? 12 : 18) : 4;
	tmp /= (reg & AD_DS_RAMC_ADST) ? 2 : 1;
	
	snd_iprintf(buffer, "Resampler FIFO: %d %s words\n\n", tmp,
			(reg & AD_DS_WSMC_WAST) ? "stereo" : "mono");
				
	
	/* doc says LSB represents -1.5dB, but the max value (-94.5dB)
	suggests that LSB is -3dB, which is more coherent with the logarithmic
	nature of the dB scale */
	reg = ad1889_readw(chip, AD_DS_WADA);
	snd_iprintf(buffer, "Left: %s, -%d dB\n",
			(reg & AD_DS_WADA_LWAM) ? "mute" : "unmute",
			((reg & AD_DS_WADA_LWAA) >> 8) * 3);
	reg = ad1889_readw(chip, AD_DS_WADA);
	snd_iprintf(buffer, "Right: %s, -%d dB\n",
			(reg & AD_DS_WADA_RWAM) ? "mute" : "unmute",
			(reg & AD_DS_WADA_RWAA) * 3);
	
	reg = ad1889_readw(chip, AD_DS_WAS);
	snd_iprintf(buffer, "Wave samplerate: %u Hz\n", reg);
	reg = ad1889_readw(chip, AD_DS_RES);
	snd_iprintf(buffer, "Resampler samplerate: %u Hz\n", reg);
}