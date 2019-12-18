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
struct buf_ref_priv {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  priv; } ;
typedef  TYPE_1__ RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 
 struct buf_ref_priv* get_priv_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool buf_ref_fini(RBuffer *b) {
	struct buf_ref_priv *priv = get_priv_ref (b);
	r_buf_free (priv->parent);
	R_FREE (b->priv);
	return true;
}