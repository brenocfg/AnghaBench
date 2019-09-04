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
struct altmode {TYPE_1__* mux; } ;
struct TYPE_2__ {int (* set ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int typec_altmode_set_mux(struct altmode *alt, u8 state)
{
	return alt->mux ? alt->mux->set(alt->mux, state) : 0;
}