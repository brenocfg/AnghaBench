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
struct buf_sparse_priv {int /*<<< orphan*/  sparse; } ;
struct TYPE_4__ {int /*<<< orphan*/  priv; } ;
typedef  TYPE_1__ RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 
 struct buf_sparse_priv* get_priv_sparse (TYPE_1__*) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool buf_sparse_fini(RBuffer *b) {
	struct buf_sparse_priv *priv = get_priv_sparse (b);
	r_list_free (priv->sparse);
	R_FREE (b->priv);
	return true;
}