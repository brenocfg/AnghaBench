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
struct skl_module_fmt {int channels; int s_freq; int bit_depth; int valid_bit_depth; int ch_cfg; int interleaving_style; int sample_type; int ch_map; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int MOD_BUF ; 
 int snprintf (char*,int,char*,char*,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static ssize_t skl_print_fmt(struct skl_module_fmt *fmt, char *buf,
					ssize_t size, bool direction)
{
	return snprintf(buf + size, MOD_BUF - size,
			"%s\n\tCh %d\n\tFreq %d\n\tBit depth %d\n\t"
			"Valid bit depth %d\n\tCh config %#x\n\tInterleaving %d\n\t"
			"Sample Type %d\n\tCh Map %#x\n",
			direction ? "Input Format:" : "Output Format:",
			fmt->channels, fmt->s_freq, fmt->bit_depth,
			fmt->valid_bit_depth, fmt->ch_cfg,
			fmt->interleaving_style, fmt->sample_type,
			fmt->ch_map);
}