#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mp_size ;
typedef  TYPE_1__* mp_int ;
struct TYPE_7__ {scalar_t__ used; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_DIGITS (TYPE_1__*) ; 
 scalar_t__ MP_USED (TYPE_1__*) ; 
 int /*<<< orphan*/  ZERO (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  s_ksqr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void
USQR(mp_int X, mp_int Z)
{
	mp_size		ua_ = MP_USED(X);
	mp_size		o_ = ua_ + ua_;

	ZERO(MP_DIGITS(Z), o_);
	(void) s_ksqr(MP_DIGITS(X), MP_DIGITS(Z), ua_);
	Z->used = o_;
	CLAMP(Z);
}