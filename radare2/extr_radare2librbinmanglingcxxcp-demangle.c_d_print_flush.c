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
struct d_print_info {char* buf; size_t len; int /*<<< orphan*/  flush_count; int /*<<< orphan*/  opaque; int /*<<< orphan*/  (* callback ) (char*,size_t,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
d_print_flush (struct d_print_info *dpi)
{
  dpi->buf[dpi->len] = '\0';
  dpi->callback (dpi->buf, dpi->len, dpi->opaque);
  dpi->len = 0;
  dpi->flush_count++;
}