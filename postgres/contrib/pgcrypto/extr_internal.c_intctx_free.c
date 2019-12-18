#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct int_ctx {scalar_t__ ptr; } ;
typedef  struct int_ctx PX_Cipher ;

/* Variables and functions */
 int /*<<< orphan*/  px_free (struct int_ctx*) ; 
 int /*<<< orphan*/  px_memset (struct int_ctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
intctx_free(PX_Cipher *c)
{
	struct int_ctx *cx = (struct int_ctx *) c->ptr;

	if (cx)
	{
		px_memset(cx, 0, sizeof *cx);
		px_free(cx);
	}
	px_free(c);
}