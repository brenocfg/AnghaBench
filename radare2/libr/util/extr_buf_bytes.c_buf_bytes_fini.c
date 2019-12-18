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
struct buf_bytes_priv {int /*<<< orphan*/  buf; scalar_t__ is_bufowner; } ;
struct TYPE_4__ {int /*<<< orphan*/  priv; } ;
typedef  TYPE_1__ RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 struct buf_bytes_priv* get_priv_bytes (TYPE_1__*) ; 

__attribute__((used)) static bool buf_bytes_fini(RBuffer *b) {
	struct buf_bytes_priv *priv = get_priv_bytes (b);
	if (priv->is_bufowner) {
		free (priv->buf);
	}
	R_FREE (b->priv);
	return true;
}