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
struct sst_dsp {void* thread_context; } ;

/* Variables and functions */

__attribute__((used)) static inline void *sst_dsp_get_thread_context(struct sst_dsp *sst)
{
	return sst->thread_context;
}