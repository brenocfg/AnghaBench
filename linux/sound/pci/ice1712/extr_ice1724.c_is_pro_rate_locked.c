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
struct snd_ice1712 {int /*<<< orphan*/  (* is_spdif_master ) (struct snd_ice1712*) ;} ;

/* Variables and functions */
 scalar_t__ PRO_RATE_LOCKED ; 
 int /*<<< orphan*/  stub1 (struct snd_ice1712*) ; 

__attribute__((used)) static inline int is_pro_rate_locked(struct snd_ice1712 *ice)
{
	return (!ice->is_spdif_master(ice)) && PRO_RATE_LOCKED;
}