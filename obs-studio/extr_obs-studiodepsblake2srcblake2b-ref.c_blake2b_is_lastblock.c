#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* f; } ;
typedef  TYPE_1__ blake2b_state ;

/* Variables and functions */

__attribute__((used)) static int blake2b_is_lastblock( const blake2b_state *S )
{
  return S->f[0] != 0;
}