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
struct snd_card {struct hdsp* private_data; } ;
struct hdsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hdsp_free (struct hdsp*) ; 

__attribute__((used)) static void snd_hdsp_card_free(struct snd_card *card)
{
	struct hdsp *hdsp = card->private_data;

	if (hdsp)
		snd_hdsp_free(hdsp);
}