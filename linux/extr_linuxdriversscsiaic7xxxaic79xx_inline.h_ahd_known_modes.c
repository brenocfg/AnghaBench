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
struct ahd_softc {void* saved_dst_mode; void* saved_src_mode; void* dst_mode; void* src_mode; } ;
typedef  void* ahd_mode ;

/* Variables and functions */

__attribute__((used)) static inline void
ahd_known_modes(struct ahd_softc *ahd, ahd_mode src, ahd_mode dst)
{
	ahd->src_mode = src;
	ahd->dst_mode = dst;
	ahd->saved_src_mode = src;
	ahd->saved_dst_mode = dst;
}