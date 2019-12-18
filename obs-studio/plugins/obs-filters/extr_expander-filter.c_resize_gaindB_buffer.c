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
struct expander_data {size_t gaindB_len; int /*<<< orphan*/ * gaindB; } ;

/* Variables and functions */
 int MAX_AUDIO_CHANNELS ; 
 int /*<<< orphan*/  brealloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void resize_gaindB_buffer(struct expander_data *cd, size_t len)
{
	cd->gaindB_len = len;
	for (int i = 0; i < MAX_AUDIO_CHANNELS; i++)
		cd->gaindB[i] =
			brealloc(cd->gaindB[i], cd->gaindB_len * sizeof(float));
}