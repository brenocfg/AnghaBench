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
struct error_desc {char const* desc; int err; } ;

/* Variables and functions */
 struct error_desc* px_err_list ; 

const char *
px_strerror(int err)
{
	const struct error_desc *e;

	for (e = px_err_list; e->desc; e++)
		if (e->err == err)
			return e->desc;
	return "Bad error code";
}