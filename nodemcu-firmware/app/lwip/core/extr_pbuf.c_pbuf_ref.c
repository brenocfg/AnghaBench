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
struct pbuf {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_ARCH_DECL_PROTECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_ARCH_PROTECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_ARCH_UNPROTECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  old_level ; 

void
pbuf_ref(struct pbuf *p)
{
  SYS_ARCH_DECL_PROTECT(old_level);
  /* pbuf given? */
  if (p != NULL) {
    SYS_ARCH_PROTECT(old_level);
    ++(p->ref);
    SYS_ARCH_UNPROTECT(old_level);
  }
}