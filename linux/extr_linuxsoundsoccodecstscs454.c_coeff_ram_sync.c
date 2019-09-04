#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cache; int /*<<< orphan*/  synced; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cache; int /*<<< orphan*/  synced; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cache; int /*<<< orphan*/  synced; } ;
struct tscs454 {TYPE_3__ sub_ram; TYPE_2__ spk_ram; TYPE_1__ dac_ram; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COEFF_RAM_COEFF_COUNT ; 
 int /*<<< orphan*/  R_DACCRADD ; 
 int /*<<< orphan*/  R_DACCRS ; 
 int /*<<< orphan*/  R_DACCRWDL ; 
 int /*<<< orphan*/  R_SPKCRADD ; 
 int /*<<< orphan*/  R_SPKCRS ; 
 int /*<<< orphan*/  R_SPKCRWDL ; 
 int /*<<< orphan*/  R_SUBCRADD ; 
 int /*<<< orphan*/  R_SUBCRS ; 
 int /*<<< orphan*/  R_SUBCRWDL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int write_coeff_ram (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int coeff_ram_sync(struct snd_soc_component *component,
		struct tscs454 *tscs454)
{
	int ret;

	mutex_lock(&tscs454->dac_ram.lock);
	if (!tscs454->dac_ram.synced) {
		ret = write_coeff_ram(component, tscs454->dac_ram.cache,
				R_DACCRS, R_DACCRADD, R_DACCRWDL,
				0x00, COEFF_RAM_COEFF_COUNT);
		if (ret < 0) {
			mutex_unlock(&tscs454->dac_ram.lock);
			return ret;
		}
	}
	mutex_unlock(&tscs454->dac_ram.lock);

	mutex_lock(&tscs454->spk_ram.lock);
	if (!tscs454->spk_ram.synced) {
		ret = write_coeff_ram(component, tscs454->spk_ram.cache,
				R_SPKCRS, R_SPKCRADD, R_SPKCRWDL,
				0x00, COEFF_RAM_COEFF_COUNT);
		if (ret < 0) {
			mutex_unlock(&tscs454->spk_ram.lock);
			return ret;
		}
	}
	mutex_unlock(&tscs454->spk_ram.lock);

	mutex_lock(&tscs454->sub_ram.lock);
	if (!tscs454->sub_ram.synced) {
		ret = write_coeff_ram(component, tscs454->sub_ram.cache,
				R_SUBCRS, R_SUBCRADD, R_SUBCRWDL,
				0x00, COEFF_RAM_COEFF_COUNT);
		if (ret < 0) {
			mutex_unlock(&tscs454->sub_ram.lock);
			return ret;
		}
	}
	mutex_unlock(&tscs454->sub_ram.lock);

	return 0;
}