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
struct TYPE_3__ {scalar_t__ k; scalar_t__ t; scalar_t__ f; } ;
typedef  TYPE_1__ expdesc ;

/* Variables and functions */
 scalar_t__ NO_JUMP ; 
 scalar_t__ VKNUM ; 

__attribute__((used)) static int isnumeral(expdesc *e) {
  return (e->k == VKNUM && e->t == NO_JUMP && e->f == NO_JUMP);
}