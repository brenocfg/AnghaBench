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
struct snd_usX2Y_substream {scalar_t__ urb; int /*<<< orphan*/  endpoint; } ;

/* Variables and functions */
 int NRURBS ; 
 int /*<<< orphan*/  snd_printdd (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usX2Y_hwdep_urb_release (scalar_t__) ; 

__attribute__((used)) static void usX2Y_usbpcm_urbs_release(struct snd_usX2Y_substream *subs)
{
	int i;
	snd_printdd("snd_usX2Y_urbs_release() %i\n", subs->endpoint);
	for (i = 0; i < NRURBS; i++)
		usX2Y_hwdep_urb_release(subs->urb + i);
}