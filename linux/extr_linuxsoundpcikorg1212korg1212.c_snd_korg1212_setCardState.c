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
struct snd_korg1212 {int cardState; } ;
typedef  enum CardState { ____Placeholder_CardState } CardState ;

/* Variables and functions */

__attribute__((used)) static inline void snd_korg1212_setCardState(struct snd_korg1212 * korg1212, enum CardState csState)
{
        korg1212->cardState = csState;
}