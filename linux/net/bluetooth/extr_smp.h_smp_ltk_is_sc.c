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
struct smp_ltk {int type; } ;

/* Variables and functions */
#define  SMP_LTK_P256 129 
#define  SMP_LTK_P256_DEBUG 128 

__attribute__((used)) static inline bool smp_ltk_is_sc(struct smp_ltk *key)
{
	switch (key->type) {
	case SMP_LTK_P256:
	case SMP_LTK_P256_DEBUG:
		return true;
	}

	return false;
}