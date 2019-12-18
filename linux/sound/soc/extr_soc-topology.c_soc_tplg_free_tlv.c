#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct soc_tplg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  p; } ;
struct snd_kcontrol_new {TYPE_1__ tlv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void soc_tplg_free_tlv(struct soc_tplg *tplg,
	struct snd_kcontrol_new *kc)
{
	kfree(kc->tlv.p);
}