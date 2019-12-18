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
struct hdspm {int dummy; } ;

/* Variables and functions */
 scalar_t__ HDSPM_outputEnableBase ; 
 int /*<<< orphan*/  hdspm_write (struct hdspm*,scalar_t__,int) ; 

__attribute__((used)) static inline void snd_hdspm_enable_out(struct hdspm * hdspm, int i, int v)
{
	hdspm_write(hdspm, HDSPM_outputEnableBase + (4 * i), v);
}