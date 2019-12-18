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
struct snd_card {int dummy; } ;
struct snd_ac97_template {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void olpc_prequirks(struct snd_card *card,
		struct snd_ac97_template *ac97) { }