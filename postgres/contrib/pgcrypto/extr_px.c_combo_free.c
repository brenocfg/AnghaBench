#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ cipher; } ;
typedef  TYPE_1__ PX_Combo ;

/* Variables and functions */
 int /*<<< orphan*/  px_cipher_free (scalar_t__) ; 
 int /*<<< orphan*/  px_free (TYPE_1__*) ; 
 int /*<<< orphan*/  px_memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
combo_free(PX_Combo *cx)
{
	if (cx->cipher)
		px_cipher_free(cx->cipher);
	px_memset(cx, 0, sizeof(*cx));
	px_free(cx);
}