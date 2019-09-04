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
struct meson_spicc_device {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SPICC_STATREG ; 
 int /*<<< orphan*/  SPICC_TF ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static inline bool meson_spicc_txfull(struct meson_spicc_device *spicc)
{
	return !!FIELD_GET(SPICC_TF,
			   readl_relaxed(spicc->base + SPICC_STATREG));
}