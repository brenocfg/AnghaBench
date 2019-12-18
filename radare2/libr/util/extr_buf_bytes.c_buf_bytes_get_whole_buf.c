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
typedef  int /*<<< orphan*/  ut64 ;
struct buf_bytes_priv {int /*<<< orphan*/ * buf; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 struct buf_bytes_priv* get_priv_bytes (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ut8 *buf_bytes_get_whole_buf(RBuffer *b, ut64 *sz) {
	struct buf_bytes_priv *priv = get_priv_bytes (b);
	if (sz) {
		*sz = priv->length;
	}
	return priv->buf;
}