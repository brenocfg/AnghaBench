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
typedef  int /*<<< orphan*/  ut64 ;
struct buf_ref_priv {int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 struct buf_ref_priv* get_priv_ref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ut64 buf_ref_get_size(RBuffer *b) {
	struct buf_ref_priv *priv = get_priv_ref (b);
	return priv->size;
}