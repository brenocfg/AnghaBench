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
struct snd_compr_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  snd_compr_fragment_elapsed (struct snd_compr_stream*) ; 

__attribute__((used)) static void sst_compr_fragment_elapsed(void *arg)
{
	struct snd_compr_stream *cstream = (struct snd_compr_stream *)arg;

	pr_debug("fragment elapsed by driver\n");
	if (cstream)
		snd_compr_fragment_elapsed(cstream);
}