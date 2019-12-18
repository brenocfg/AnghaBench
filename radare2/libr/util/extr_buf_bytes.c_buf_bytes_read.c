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
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
struct buf_bytes_priv {scalar_t__ length; scalar_t__ offset; scalar_t__ buf; } ;
typedef  scalar_t__ st64 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 scalar_t__ R_MIN (scalar_t__,scalar_t__) ; 
 struct buf_bytes_priv* get_priv_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static st64 buf_bytes_read(RBuffer *b, ut8 *buf, ut64 len) {
	struct buf_bytes_priv *priv = get_priv_bytes (b);
	ut64 real_len = priv->length < priv->offset? 0: R_MIN (priv->length - priv->offset, len);
	memmove (buf, priv->buf + priv->offset, real_len);
	priv->offset += real_len;
	return real_len;
}