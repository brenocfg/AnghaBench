#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* anal; } ;
struct TYPE_5__ {int bits; } ;
typedef  TYPE_2__ RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  REIL_SUB ; 
 int reil_mem_bineq_n (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool reil_mem_subeq(RAnalEsil *esil)  { return reil_mem_bineq_n(esil, REIL_SUB, esil->anal->bits / 8); }