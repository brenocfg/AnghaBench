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
struct rme96 {unsigned int playback_frlog; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ RME96_IO_GET_PLAY_POS ; 
 unsigned int RME96_RCR_AUDIO_ADDR_MASK ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static inline unsigned int
snd_rme96_playback_ptr(struct rme96 *rme96)
{
	return (readl(rme96->iobase + RME96_IO_GET_PLAY_POS)
		& RME96_RCR_AUDIO_ADDR_MASK) >> rme96->playback_frlog;
}