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
struct _reent {int dummy; } ;
typedef  size_t _ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  os_putc (char) ; 

_ssize_t _write_r(struct _reent *r, int fd, void *buf, size_t len) {
  if (fd == 1 || fd == 2) {
    size_t i;
    for (i = 0; i < len; i++) {
      os_putc(((char *) buf)[i]);
    }
    return len;
  }
  return -1;
}