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
typedef  int /*<<< orphan*/  v ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u ;
struct TYPE_3__ {int /*<<< orphan*/ * tables; int /*<<< orphan*/ * state; } ;
typedef  TYPE_1__ PHP_GOST_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  PASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHIFT12 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHIFT16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHIFT61 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void Gost(PHP_GOST_CTX *context, uint32_t data[8])
{
	int i;
	uint32_t l, r, t, key[8], u[8], v[8], w[8], s[8], *h = context->state, *m = data;

	memcpy(u, context->state, sizeof(u));
	memcpy(v, data, sizeof(v));

	for (i = 0; i < 8; i += 2) {
		PASS(*context->tables);
	}
	SHIFT12(u, m, s);
	SHIFT16(h, v, u);
	SHIFT61(h, v);
}