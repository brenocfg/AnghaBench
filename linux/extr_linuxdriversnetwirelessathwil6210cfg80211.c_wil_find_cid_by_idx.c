#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct wil6210_priv {TYPE_1__* sta; } ;
struct TYPE_2__ {scalar_t__ status; scalar_t__ mid; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOENT ; 
 scalar_t__ wil_sta_unused ; 

__attribute__((used)) static int wil_find_cid_by_idx(struct wil6210_priv *wil, u8 mid, int idx)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(wil->sta); i++) {
		if (wil->sta[i].status == wil_sta_unused)
			continue;
		if (wil->sta[i].mid != mid)
			continue;
		if (idx == 0)
			return i;
		idx--;
	}

	return -ENOENT;
}