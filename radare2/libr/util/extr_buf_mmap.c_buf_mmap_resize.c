#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
struct TYPE_3__ {scalar_t__ length; int /*<<< orphan*/ * buf; } ;
struct buf_mmap_priv {TYPE_1__ bytes_priv; TYPE_2__* mmap; } ;
struct TYPE_4__ {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 struct buf_mmap_priv* get_priv_mmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_mem_mmap_resize (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static bool buf_mmap_resize(RBuffer *b, ut64 newsize) {
	struct buf_mmap_priv *priv = get_priv_mmap (b);
	if (newsize > priv->mmap->len) {
		ut8 *t = r_mem_mmap_resize (priv->mmap, newsize);
		if (!t) {
			return false;
		}
		priv->bytes_priv.buf = t;
	}
	priv->bytes_priv.length = newsize;
	return true;
}