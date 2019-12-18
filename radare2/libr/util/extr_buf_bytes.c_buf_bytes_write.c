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
struct buf_bytes_priv {scalar_t__ offset; scalar_t__ length; scalar_t__ buf; } ;
typedef  int st64 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 struct buf_bytes_priv* get_priv_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (scalar_t__,int /*<<< orphan*/  const*,scalar_t__) ; 
 int r_buf_resize (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static st64 buf_bytes_write(RBuffer *b, const ut8 *buf, ut64 len) {
	struct buf_bytes_priv *priv = get_priv_bytes (b);
	if (priv->offset > priv->length || priv->offset + len >= priv->length) {
		bool r = r_buf_resize (b, priv->offset + len);
		if (!r) {
			return -1;
		}
	}
	memmove (priv->buf + priv->offset, buf, len);
	priv->offset += len;
	return len;
}