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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int* state; } ;
struct qman_cgrs {TYPE_1__ q; } ;

/* Variables and functions */
 int CGR_BIT (int /*<<< orphan*/ ) ; 
 size_t CGR_WORD (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int qman_cgrs_get(struct qman_cgrs *c, u8 cgr)
{
	return c->q.state[CGR_WORD(cgr)] & CGR_BIT(cgr);
}