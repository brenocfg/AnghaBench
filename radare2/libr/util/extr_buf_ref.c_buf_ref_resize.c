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
typedef  scalar_t__ ut64 ;
struct buf_ref_priv {scalar_t__ base; int /*<<< orphan*/  size; int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  R_MIN (scalar_t__,scalar_t__) ; 
 struct buf_ref_priv* get_priv_ref (int /*<<< orphan*/ *) ; 
 scalar_t__ r_buf_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool buf_ref_resize(RBuffer *b, ut64 newsize) {
	struct buf_ref_priv *priv = get_priv_ref (b);
	ut64 parent_sz = r_buf_size (priv->parent);
	priv->size = R_MIN (parent_sz - priv->base, newsize);
	return true;
}