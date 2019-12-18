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
struct snd_motu_packet_format {unsigned char* differed_part_pcm_chunks; } ;
typedef  enum snd_motu_spec_flags { ____Placeholder_snd_motu_spec_flags } snd_motu_spec_flags ;

/* Variables and functions */
 int SND_MOTU_SPEC_HAS_OPT_IFACE_A ; 
 int SND_MOTU_SPEC_HAS_OPT_IFACE_B ; 
 unsigned char round_up (unsigned char,int) ; 

__attribute__((used)) static void calculate_differed_part(struct snd_motu_packet_format *formats,
				    enum snd_motu_spec_flags flags, u32 data,
				    u32 a_enable_mask, u32 a_no_adat_mask,
				    u32 b_enable_mask, u32 b_no_adat_mask)
{
	unsigned char pcm_chunks[3] = {0, 0, 0};
	int i;

	if ((flags & SND_MOTU_SPEC_HAS_OPT_IFACE_A) && (data & a_enable_mask)) {
		if (data & a_no_adat_mask) {
			/*
			 * Additional two data chunks for S/PDIF on optical
			 * interface A. This includes empty data chunks.
			 */
			pcm_chunks[0] += 4;
			pcm_chunks[1] += 4;
		} else {
			/*
			 * Additional data chunks for ADAT on optical interface
			 * A.
			 */
			pcm_chunks[0] += 8;
			pcm_chunks[1] += 4;
		}
	}

	if ((flags & SND_MOTU_SPEC_HAS_OPT_IFACE_B) && (data & b_enable_mask)) {
		if (data & b_no_adat_mask) {
			/*
			 * Additional two data chunks for S/PDIF on optical
			 * interface B. This includes empty data chunks.
			 */
			pcm_chunks[0] += 4;
			pcm_chunks[1] += 4;
		} else {
			/*
			 * Additional data chunks for ADAT on optical interface
			 * B.
			 */
			pcm_chunks[0] += 8;
			pcm_chunks[1] += 4;
		}
	}

	for (i = 0; i < 3; ++i) {
		if (pcm_chunks[i] > 0)
			pcm_chunks[i] = round_up(pcm_chunks[i], 4);

		formats->differed_part_pcm_chunks[i] = pcm_chunks[i];
	}
}