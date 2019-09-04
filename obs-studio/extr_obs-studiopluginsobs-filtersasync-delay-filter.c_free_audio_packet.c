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
struct obs_audio_data {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 size_t MAX_AV_PLANES ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct obs_audio_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void free_audio_packet(struct obs_audio_data *audio)
{
	for (size_t i = 0; i < MAX_AV_PLANES; i++)
		bfree(audio->data[i]);
	memset(audio, 0, sizeof(*audio));
}