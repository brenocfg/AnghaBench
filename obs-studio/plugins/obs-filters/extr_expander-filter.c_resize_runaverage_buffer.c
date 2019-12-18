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
struct expander_data {size_t runaverage_len; int /*<<< orphan*/ * runaverage; } ;

/* Variables and functions */
 int MAX_AUDIO_CHANNELS ; 
 int /*<<< orphan*/  brealloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void resize_runaverage_buffer(struct expander_data *cd, size_t len)
{
	cd->runaverage_len = len;
	for (int i = 0; i < MAX_AUDIO_CHANNELS; i++)
		cd->runaverage[i] = brealloc(
			cd->runaverage[i], cd->runaverage_len * sizeof(float));
}