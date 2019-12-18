#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_ac97 {int id; TYPE_1__* bus; } ;
struct TYPE_4__ {int (* read ) (struct snd_ac97*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {TYPE_2__* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_VENDOR_ID1 ; 
 int /*<<< orphan*/  AC97_VENDOR_ID2 ; 
 int stub1 (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int stub2 (struct snd_ac97*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool snd_ac97_check_id(struct snd_ac97 *ac97, unsigned int id,
	unsigned int id_mask)
{
	ac97->id = ac97->bus->ops->read(ac97, AC97_VENDOR_ID1) << 16;
	ac97->id |= ac97->bus->ops->read(ac97, AC97_VENDOR_ID2);

	if (ac97->id == 0x0 || ac97->id == 0xffffffff)
		return false;

	if (id != 0 && id != (ac97->id & id_mask))
		return false;

	return true;
}