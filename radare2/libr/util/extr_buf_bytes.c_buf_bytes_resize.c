#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
struct buf_bytes_priv {scalar_t__ length; int /*<<< orphan*/ * buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  Oxff_priv; } ;
typedef  TYPE_1__ RBuffer ;

/* Variables and functions */
 struct buf_bytes_priv* get_priv_bytes (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static bool buf_bytes_resize(RBuffer *b, ut64 newsize) {
	struct buf_bytes_priv *priv = get_priv_bytes (b);
	if (newsize > priv->length) {
		ut8 *t = realloc (priv->buf, newsize);
		if (!t) {
			return false;
		}
		priv->buf = t;
		memset (priv->buf + priv->length, b->Oxff_priv, newsize - priv->length);
	}
	priv->length = newsize;
	return true;
}