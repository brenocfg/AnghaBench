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
struct tsm_vte {int dummy; } ;
typedef  int /*<<< orphan*/  out ;

/* Variables and functions */

__attribute__((used)) static void terminal_write_fn(struct tsm_vte *vte,
			      const char *u8,
			      size_t len,
			      void *data)
{
  // try to access the written data
  static char out[4096];
  while (len--)
    out[len % sizeof(out)] = u8[len];
}