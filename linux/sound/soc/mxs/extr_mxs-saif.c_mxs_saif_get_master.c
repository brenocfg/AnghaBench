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
struct mxs_saif {size_t master_id; } ;

/* Variables and functions */
 struct mxs_saif** mxs_saif ; 

__attribute__((used)) static inline struct mxs_saif *mxs_saif_get_master(struct mxs_saif * saif)
{
	return mxs_saif[saif->master_id];
}