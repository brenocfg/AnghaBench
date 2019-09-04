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
typedef  int /*<<< orphan*/  u16 ;
struct request_context {int dummy; } ;
struct hermes {struct ezusb_priv* priv; } ;
struct ezusb_priv {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EZUSB_FRAME_CONTROL ; 
 int ezusb_access_ltv (struct ezusb_priv*,struct request_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ *) ; 
 struct request_context* ezusb_alloc_ctx (struct ezusb_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ezusb_read_ltv(struct hermes *hw, int bap, u16 rid,
			  unsigned bufsize, u16 *length, void *buf)
{
	struct ezusb_priv *upriv = hw->priv;
	struct request_context *ctx;

	if (bufsize % 2)
		return -EINVAL;

	ctx = ezusb_alloc_ctx(upriv, rid, rid);
	if (!ctx)
		return -ENOMEM;

	return ezusb_access_ltv(upriv, ctx, 0, NULL, EZUSB_FRAME_CONTROL,
				buf, bufsize, length);
}