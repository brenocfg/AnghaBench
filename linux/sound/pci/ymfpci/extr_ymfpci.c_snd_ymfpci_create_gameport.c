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
struct snd_ymfpci {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 

__attribute__((used)) static inline int snd_ymfpci_create_gameport(struct snd_ymfpci *chip, int dev, int l, int l2) { return -ENOSYS; }