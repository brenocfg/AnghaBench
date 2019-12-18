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
struct expander_data {struct expander_data* env_in; struct expander_data** gaindB; struct expander_data** runaverage; struct expander_data** envelope_buf; } ;

/* Variables and functions */
 int MAX_AUDIO_CHANNELS ; 
 int /*<<< orphan*/  bfree (struct expander_data*) ; 

__attribute__((used)) static void expander_destroy(void *data)
{
	struct expander_data *cd = data;

	for (int i = 0; i < MAX_AUDIO_CHANNELS; i++) {
		bfree(cd->envelope_buf[i]);
		bfree(cd->runaverage[i]);
		bfree(cd->gaindB[i]);
	}
	bfree(cd->env_in);
	bfree(cd);
}