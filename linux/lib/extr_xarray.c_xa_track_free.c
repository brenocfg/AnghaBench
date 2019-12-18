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
struct xarray {int xa_flags; } ;

/* Variables and functions */
 int XA_FLAGS_TRACK_FREE ; 

__attribute__((used)) static inline bool xa_track_free(const struct xarray *xa)
{
	return xa->xa_flags & XA_FLAGS_TRACK_FREE;
}