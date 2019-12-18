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
struct gs_vb_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ bzalloc (int) ; 

__attribute__((used)) static inline struct gs_vb_data *gs_vbdata_create(void)
{
	return (struct gs_vb_data *)bzalloc(sizeof(struct gs_vb_data));
}