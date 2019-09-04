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
struct snd_usX2Y_substream {scalar_t__ transfer_done; scalar_t__ hwptr_done; scalar_t__ hwptr; int /*<<< orphan*/ * urb; int /*<<< orphan*/  endpoint; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_printdd (char*,struct snd_usX2Y_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usX2Y_subs_prepare(struct snd_usX2Y_substream *subs)
{
	snd_printdd("usX2Y_substream_prepare(%p) ep=%i urb0=%p urb1=%p\n",
		    subs, subs->endpoint, subs->urb[0], subs->urb[1]);
	/* reset the pointer */
	subs->hwptr = 0;
	subs->hwptr_done = 0;
	subs->transfer_done = 0;
}