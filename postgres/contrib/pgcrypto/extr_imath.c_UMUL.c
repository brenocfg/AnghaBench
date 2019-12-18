#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mp_size ;
typedef  TYPE_1__* mp_int ;
struct TYPE_8__ {scalar_t__ used; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_DIGITS (TYPE_1__*) ; 
 scalar_t__ MP_USED (TYPE_1__*) ; 
 int /*<<< orphan*/  ZERO (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  s_kmul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void
UMUL(mp_int X, mp_int Y, mp_int Z)
{
	mp_size		ua_ = MP_USED(X);
	mp_size		ub_ = MP_USED(Y);
	mp_size		o_ = ua_ + ub_;

	ZERO(MP_DIGITS(Z), o_);
	(void) s_kmul(MP_DIGITS(X), MP_DIGITS(Y), MP_DIGITS(Z), ua_, ub_);
	Z->used = o_;
	CLAMP(Z);
}