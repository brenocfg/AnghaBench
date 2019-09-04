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
struct michael_mic {scalar_t__ m_bytes; int /*<<< orphan*/  k1; int /*<<< orphan*/  r; int /*<<< orphan*/  k0; int /*<<< orphan*/  l; } ;

/* Variables and functions */

__attribute__((used)) static inline void michael_clear(struct michael_mic *mic)
{
	mic->l = mic->k0;
	mic->r = mic->k1;
	mic->m_bytes = 0;
}