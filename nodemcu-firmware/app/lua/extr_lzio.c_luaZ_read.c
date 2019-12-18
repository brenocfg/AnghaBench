#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t n; size_t p; size_t i; } ;
typedef  TYPE_1__ ZIO ;

/* Variables and functions */
 scalar_t__ EOZ ; 
 scalar_t__ luaZ_lookahead (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (void*,size_t,size_t) ; 

size_t luaZ_read (ZIO *z, void *b, size_t n) {
  while (n) {
    size_t m;
    if (luaZ_lookahead(z) == EOZ)
      return n;  /* return number of missing bytes */
    m = (n <= z->n) ? n : z->n;  /* min. between n and z->n */
    if (b)
      memcpy(b, z->p, m);
    z->n -= m;
    z->i += m;
    z->p += m;
    if (b)
      b = (char *)b + m;
    n -= m;
  }
  return 0;
}