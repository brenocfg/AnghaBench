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
struct gs_init_data {int dummy; } ;
struct gl_windowinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (struct gs_init_data const*) ; 
 struct gl_windowinfo* bmalloc (int) ; 

extern struct gl_windowinfo *
gl_windowinfo_create(const struct gs_init_data *info)
{
	UNUSED_PARAMETER(info);
	return bmalloc(sizeof(struct gl_windowinfo));
}