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
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Keyword ;

/* Variables and functions */
 int memicmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compKeyword(const void *m1, const void *m2){
  const Keyword *k1 = m1, *k2 = m2;
  int ret, len = min( k1->len, k2->len );

  if ((ret = memicmpW( k1->name, k2->name, len ))) return ret;
  if (k1->len < k2->len) return -1;
  else if (k1->len > k2->len) return 1;
  return 0;
}